#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <vector>
#include <nlohmann/json.hpp>
#include <set>

using json = nlohmann::json;
namespace fs = std::filesystem;

// 本地文件操作类
class LocalFileClient {
public:
    LocalFileClient(const std::string& config_path = "config.json") {
        // 默认值
        base_path = "./data";
        allowed_ops = {"create", "read", "delete", "list", "search"};
        // 读取配置
        std::ifstream config_file(config_path);
        if (config_file.is_open()) {
            try {
                json config;
                config_file >> config;
                if (config.contains("local-file-server")) {
                    auto local_conf = config["local-file-server"];
                    if (local_conf.contains("base_path")) {
                        base_path = local_conf["base_path"].get<std::string>();
                    }
                    if (local_conf.contains("allowed_ops")) {
                        allowed_ops.clear();
                        for (const auto& op : local_conf["allowed_ops"]) {
                            allowed_ops.insert(op.get<std::string>());
                        }
                    }
                }
            } catch (...) {
                // ignore parse error, use default
            }
        }
        fs::create_directories(base_path);
    }
    
    // 创建文件
    json createFile(const std::string& filename, const std::string& content) {
        if (!isAllowed("create")) return {{"success", false}, {"message", "Operation not allowed"}};
        try {
            fs::path filepath = base_path / filename;
            std::ofstream file(filepath);
            if (file.is_open()) {
                file << content;
                file.close();
                return {
                    {"success", true},
                    {"message", "File created successfully"},
                    {"filename", filename},
                    {"size", content.length()}
                };
            }
            return {{"success", false}, {"message", "Failed to create file"}};
        } catch (const std::exception& e) {
            return {{"success", false}, {"message", e.what()}};
        }
    }
    
    // 读取文件
    json readFile(const std::string& filename) {
        if (!isAllowed("read")) return {{"success", false}, {"message", "Operation not allowed"}};
        try {
            fs::path filepath = base_path / filename;
            if (!fs::exists(filepath)) {
                return {{"success", false}, {"message", "File not found"}};
            }
            
            std::ifstream file(filepath);
            if (file.is_open()) {
                std::string content((std::istreambuf_iterator<char>(file)),
                                   std::istreambuf_iterator<char>());
                file.close();
                return {
                    {"success", true},
                    {"filename", filename},
                    {"content", content},
                    {"size", content.length()}
                };
            }
            return {{"success", false}, {"message", "Failed to read file"}};
        } catch (const std::exception& e) {
            return {{"success", false}, {"message", e.what()}};
        }
    }
    
    // 列出文件
    json listFiles() {
        if (!isAllowed("list")) return {{"success", false}, {"message", "Operation not allowed"}};
        try {
            std::vector<json> files;
            for (const auto& entry : fs::directory_iterator(base_path)) {
                if (entry.is_regular_file()) {
                    files.push_back({
                        {"name", entry.path().filename().string()},
                        {"size", entry.file_size()}
                    });
                }
            }
            return {
                {"success", true},
                {"files", files},
                {"count", files.size()}
            };
        } catch (const std::exception& e) {
            return {{"success", false}, {"message", e.what()}};
        }
    }
    
    // 删除文件
    json deleteFile(const std::string& filename) {
        if (!isAllowed("delete")) return {{"success", false}, {"message", "Operation not allowed"}};
        try {
            fs::path filepath = base_path / filename;
            if (!fs::exists(filepath)) {
                return {{"success", false}, {"message", "File not found"}};
            }
            
            if (fs::remove(filepath)) {
                return {
                    {"success", true},
                    {"message", "File deleted successfully"},
                    {"filename", filename}
                };
            }
            return {{"success", false}, {"message", "Failed to delete file"}};
        } catch (const std::exception& e) {
            return {{"success", false}, {"message", e.what()}};
        }
    }
    
    // 搜索文件
    json searchFiles(const std::string& pattern) {
        if (!isAllowed("search")) return {{"success", false}, {"message", "Operation not allowed"}};
        try {
            std::vector<json> matches;
            for (const auto& entry : fs::directory_iterator(base_path)) {
                if (entry.is_regular_file()) {
                    std::string filename = entry.path().filename().string();
                    if (filename.find(pattern) != std::string::npos) {
                        matches.push_back({
                            {"name", filename},
                            {"size", entry.file_size()}
                        });
                    }
                }
            }
            return {
                {"success", true},
                {"pattern", pattern},
                {"matches", matches},
                {"count", matches.size()}
            };
        } catch (const std::exception& e) {
            return {{"success", false}, {"message", e.what()}};
        }
    }

private:
    fs::path base_path;
    std::set<std::string> allowed_ops;
    bool isAllowed(const std::string& op) const {
        return allowed_ops.count(op) > 0;
    }
};

int main() {
    std::cout << "=== Local File Operations Example ===" << std::endl;
    
    LocalFileClient client("config.json");
    
    try {
        // Step 1: 创建文件
        std::cout << "\n[Step 1] Creating test file..." << std::endl;
        json createResult = client.createFile("test.txt", "Hello, Local File Client!\nThis is a test file.\n");
        
        if (createResult["success"]) {
            std::cout << "✅ File created successfully!" << std::endl;
            std::cout << "   Size: " << createResult["size"] << " bytes" << std::endl;
        } else {
            std::cerr << "❌ File creation failed: " << createResult["message"] << std::endl;
        }
        
        // Step 2: 读取文件
        std::cout << "\n[Step 2] Reading test file..." << std::endl;
        json readResult = client.readFile("test.txt");
        
        if (readResult["success"]) {
            std::cout << "✅ File read successfully!" << std::endl;
            std::cout << "   Content: " << readResult["content"] << std::endl;
        } else {
            std::cerr << "❌ File read failed: " << readResult["message"] << std::endl;
        }
        
        // Step 3: 列出文件
        std::cout << "\n[Step 3] Listing files..." << std::endl;
        json listResult = client.listFiles();
        
        if (listResult["success"]) {
            std::cout << "✅ Files listed successfully!" << std::endl;
            std::cout << "   Found " << listResult["count"] << " files:" << std::endl;
            for (const auto& file : listResult["files"]) {
                std::cout << "   📄 " << file["name"] << " (" << file["size"] << " bytes)" << std::endl;
            }
        } else {
            std::cerr << "❌ File listing failed: " << listResult["message"] << std::endl;
        }
        
        // Step 4: 搜索文件
        std::cout << "\n[Step 4] Searching for files..." << std::endl;
        json searchResult = client.searchFiles("test");
        
        if (searchResult["success"]) {
            std::cout << "✅ File search completed!" << std::endl;
            std::cout << "   Pattern: " << searchResult["pattern"] << std::endl;
            std::cout << "   Found " << searchResult["count"] << " matches:" << std::endl;
            for (const auto& match : searchResult["matches"]) {
                std::cout << "   🔍 " << match["name"] << std::endl;
            }
        } else {
            std::cerr << "❌ File search failed: " << searchResult["message"] << std::endl;
        }
        
        // Step 5: 创建更多文件
        std::cout << "\n[Step 5] Creating additional files..." << std::endl;
        
        client.createFile("config.json", R"({
    "server": "local-file-server",
    "version": "1.0.0"
})");
        std::cout << "✅ Config file created!" << std::endl;
        
        client.createFile("app.log", "2024-01-01 10:00:00 INFO: Application started\n");
        std::cout << "✅ Log file created!" << std::endl;
        
        // Step 6: 删除测试文件
        std::cout << "\n[Step 6] Cleaning up..." << std::endl;
        json deleteResult = client.deleteFile("test.txt");
        
        if (deleteResult["success"]) {
            std::cout << "✅ Test file deleted successfully!" << std::endl;
        } else {
            std::cerr << "❌ File deletion failed: " << deleteResult["message"] << std::endl;
        }
        
    } catch (const std::exception& e) {
        std::cerr << "❌ Error: " << e.what() << std::endl;
        return 1;
    }
    
    std::cout << "\n🎉 Local file operations completed successfully!" << std::endl;
    std::cout << "   Check the ./data directory for created files." << std::endl;
    
    return 0;
} 