//  To parse this JSON data, first install
//
//      Boost     http://www.boost.org
//      json.hpp  https://github.com/nlohmann/json
//
//  Then include this file, and then do
//
//     Schema data = nlohmann::json::parse(jsonString);

#pragma once

#include <boost/optional.hpp>
#include "json.hpp"

#include <boost/optional.hpp>
#include <stdexcept>
#include <regex>

#ifndef NLOHMANN_OPT_HELPER
#define NLOHMANN_OPT_HELPER
namespace nlohmann {
    template <typename T>
    struct adl_serializer<std::shared_ptr<T>> {
        static void to_json(json & j, const std::shared_ptr<T> & opt) {
            if (!opt) j = nullptr; else j = *opt;
        }

        static std::shared_ptr<T> from_json(const json & j) {
            if (j.is_null()) return std::make_shared<T>(); else return std::make_shared<T>(j.get<T>());
        }
    };
    template <typename T>
    struct adl_serializer<boost::optional<T>> {
        static void to_json(json & j, const boost::optional<T> & opt) {
            if (!opt) j = nullptr; else j = *opt;
        }

        static boost::optional<T> from_json(const json & j) {
            if (j.is_null()) return boost::optional<T>(); else return boost::optional<T>(j.get<T>());
        }
    };
}
#endif

namespace quicktype {
    using nlohmann::json;

    #ifndef NLOHMANN_UNTYPED_quicktype_HELPER
    #define NLOHMANN_UNTYPED_quicktype_HELPER
    inline json get_untyped(const json & j, const char * property) {
        if (j.find(property) != j.end()) {
            return j.at(property).get<json>();
        }
        return json();
    }

    inline json get_untyped(const json & j, std::string property) {
        return get_untyped(j, property.data());
    }
    #endif

    #ifndef NLOHMANN_OPTIONAL_quicktype_HELPER
    #define NLOHMANN_OPTIONAL_quicktype_HELPER
    template <typename T>
    inline std::shared_ptr<T> get_heap_optional(const json & j, const char * property) {
        auto it = j.find(property);
        if (it != j.end() && !it->is_null()) {
            return j.at(property).get<std::shared_ptr<T>>();
        }
        return std::shared_ptr<T>();
    }

    template <typename T>
    inline std::shared_ptr<T> get_heap_optional(const json & j, std::string property) {
        return get_heap_optional<T>(j, property.data());
    }
    template <typename T>
    inline boost::optional<T> get_stack_optional(const json & j, const char * property) {
        auto it = j.find(property);
        if (it != j.end() && !it->is_null()) {
            return j.at(property).get<boost::optional<T>>();
        }
        return boost::optional<T>();
    }

    template <typename T>
    inline boost::optional<T> get_stack_optional(const json & j, std::string property) {
        return get_stack_optional<T>(j, property.data());
    }
    #endif

    class EmptyResult {
        public:
        EmptyResult() = default;
        virtual ~EmptyResult() = default;

        private:
        std::string ref;

        public:
        const std::string & get_ref() const { return ref; }
        std::string & get_mutable_ref() { return ref; }
        void set_ref(const std::string & value) { this->ref = value; }
    };

    class Audience {
        public:
        Audience() = default;
        virtual ~Audience() = default;

        private:
        std::string description;
        EmptyResult items;
        std::string type;

        public:
        const std::string & get_description() const { return description; }
        std::string & get_mutable_description() { return description; }
        void set_description(const std::string & value) { this->description = value; }

        const EmptyResult & get_items() const { return items; }
        EmptyResult & get_mutable_items() { return items; }
        void set_items(const EmptyResult & value) { this->items = value; }

        const std::string & get_type() const { return type; }
        std::string & get_mutable_type() { return type; }
        void set_type(const std::string & value) { this->type = value; }
    };

    enum class TypeElement : int { BOOLEAN, INTEGER, NUMBER, STRING };

    class Priority {
        public:
        Priority() = default;
        virtual ~Priority() = default;

        private:
        std::string description;
        int64_t maximum;
        int64_t minimum;
        TypeElement type;

        public:
        const std::string & get_description() const { return description; }
        std::string & get_mutable_description() { return description; }
        void set_description(const std::string & value) { this->description = value; }

        const int64_t & get_maximum() const { return maximum; }
        int64_t & get_mutable_maximum() { return maximum; }
        void set_maximum(const int64_t & value) { this->maximum = value; }

        const int64_t & get_minimum() const { return minimum; }
        int64_t & get_mutable_minimum() { return minimum; }
        void set_minimum(const int64_t & value) { this->minimum = value; }

        const TypeElement & get_type() const { return type; }
        TypeElement & get_mutable_type() { return type; }
        void set_type(const TypeElement & value) { this->type = value; }
    };

    class AnnotationsProperties {
        public:
        AnnotationsProperties() = default;
        virtual ~AnnotationsProperties() = default;

        private:
        Audience audience;
        Priority priority;

        public:
        const Audience & get_audience() const { return audience; }
        Audience & get_mutable_audience() { return audience; }
        void set_audience(const Audience & value) { this->audience = value; }

        const Priority & get_priority() const { return priority; }
        Priority & get_mutable_priority() { return priority; }
        void set_priority(const Priority & value) { this->priority = value; }
    };

    enum class AnnotationsType : int { OBJECT };

    class Annotations {
        public:
        Annotations() = default;
        virtual ~Annotations() = default;

        private:
        std::string description;
        AnnotationsProperties properties;
        AnnotationsType type;

        public:
        const std::string & get_description() const { return description; }
        std::string & get_mutable_description() { return description; }
        void set_description(const std::string & value) { this->description = value; }

        const AnnotationsProperties & get_properties() const { return properties; }
        AnnotationsProperties & get_mutable_properties() { return properties; }
        void set_properties(const AnnotationsProperties & value) { this->properties = value; }

        const AnnotationsType & get_type() const { return type; }
        AnnotationsType & get_mutable_type() { return type; }
        void set_type(const AnnotationsType & value) { this->type = value; }
    };

    class AnnotationsClass {
        public:
        AnnotationsClass() = default;
        virtual ~AnnotationsClass() = default;

        private:
        std::string ref;
        std::string description;

        public:
        const std::string & get_ref() const { return ref; }
        std::string & get_mutable_ref() { return ref; }
        void set_ref(const std::string & value) { this->ref = value; }

        const std::string & get_description() const { return description; }
        std::string & get_mutable_description() { return description; }
        void set_description(const std::string & value) { this->description = value; }
    };

    enum class Required : int { BYTE, URI, URI_TEMPLATE };

    class BlobClass {
        public:
        BlobClass() = default;
        virtual ~BlobClass() = default;

        private:
        std::string description;
        Required format;
        TypeElement type;

        public:
        const std::string & get_description() const { return description; }
        std::string & get_mutable_description() { return description; }
        void set_description(const std::string & value) { this->description = value; }

        const Required & get_format() const { return format; }
        Required & get_mutable_format() { return format; }
        void set_format(const Required & value) { this->format = value; }

        const TypeElement & get_type() const { return type; }
        TypeElement & get_mutable_type() { return type; }
        void set_type(const TypeElement & value) { this->type = value; }
    };

    class Cursor {
        public:
        Cursor() = default;
        virtual ~Cursor() = default;

        private:
        std::string description;
        TypeElement type;

        public:
        const std::string & get_description() const { return description; }
        std::string & get_mutable_description() { return description; }
        void set_description(const std::string & value) { this->description = value; }

        const TypeElement & get_type() const { return type; }
        TypeElement & get_mutable_type() { return type; }
        void set_type(const TypeElement & value) { this->type = value; }
    };

    class TypeClass {
        public:
        TypeClass() = default;
        virtual ~TypeClass() = default;

        private:
        std::string type_const;
        TypeElement type;

        public:
        const std::string & get_type_const() const { return type_const; }
        std::string & get_mutable_type_const() { return type_const; }
        void set_type_const(const std::string & value) { this->type_const = value; }

        const TypeElement & get_type() const { return type; }
        TypeElement & get_mutable_type() { return type; }
        void set_type(const TypeElement & value) { this->type = value; }
    };

    class AudioContentProperties {
        public:
        AudioContentProperties() = default;
        virtual ~AudioContentProperties() = default;

        private:
        AnnotationsClass annotations;
        BlobClass data;
        Cursor mime_type;
        TypeClass type;

        public:
        const AnnotationsClass & get_annotations() const { return annotations; }
        AnnotationsClass & get_mutable_annotations() { return annotations; }
        void set_annotations(const AnnotationsClass & value) { this->annotations = value; }

        const BlobClass & get_data() const { return data; }
        BlobClass & get_mutable_data() { return data; }
        void set_data(const BlobClass & value) { this->data = value; }

        const Cursor & get_mime_type() const { return mime_type; }
        Cursor & get_mutable_mime_type() { return mime_type; }
        void set_mime_type(const Cursor & value) { this->mime_type = value; }

        const TypeClass & get_type() const { return type; }
        TypeClass & get_mutable_type() { return type; }
        void set_type(const TypeClass & value) { this->type = value; }
    };

    class Content {
        public:
        Content() = default;
        virtual ~Content() = default;

        private:
        std::string description;
        AudioContentProperties properties;
        std::vector<std::string> required;
        AnnotationsType type;

        public:
        const std::string & get_description() const { return description; }
        std::string & get_mutable_description() { return description; }
        void set_description(const std::string & value) { this->description = value; }

        const AudioContentProperties & get_properties() const { return properties; }
        AudioContentProperties & get_mutable_properties() { return properties; }
        void set_properties(const AudioContentProperties & value) { this->properties = value; }

        const std::vector<std::string> & get_required() const { return required; }
        std::vector<std::string> & get_mutable_required() { return required; }
        void set_required(const std::vector<std::string> & value) { this->required = value; }

        const AnnotationsType & get_type() const { return type; }
        AnnotationsType & get_mutable_type() { return type; }
        void set_type(const AnnotationsType & value) { this->type = value; }
    };

    class BlobResourceContentsProperties {
        public:
        BlobResourceContentsProperties() = default;
        virtual ~BlobResourceContentsProperties() = default;

        private:
        BlobClass blob;
        Cursor mime_type;
        BlobClass uri;

        public:
        const BlobClass & get_blob() const { return blob; }
        BlobClass & get_mutable_blob() { return blob; }
        void set_blob(const BlobClass & value) { this->blob = value; }

        const Cursor & get_mime_type() const { return mime_type; }
        Cursor & get_mutable_mime_type() { return mime_type; }
        void set_mime_type(const Cursor & value) { this->mime_type = value; }

        const BlobClass & get_uri() const { return uri; }
        BlobClass & get_mutable_uri() { return uri; }
        void set_uri(const BlobClass & value) { this->uri = value; }
    };

    class BlobResourceContents {
        public:
        BlobResourceContents() = default;
        virtual ~BlobResourceContents() = default;

        private:
        BlobResourceContentsProperties properties;
        std::vector<std::string> required;
        AnnotationsType type;

        public:
        const BlobResourceContentsProperties & get_properties() const { return properties; }
        BlobResourceContentsProperties & get_mutable_properties() { return properties; }
        void set_properties(const BlobResourceContentsProperties & value) { this->properties = value; }

        const std::vector<std::string> & get_required() const { return required; }
        std::vector<std::string> & get_mutable_required() { return required; }
        void set_required(const std::vector<std::string> & value) { this->required = value; }

        const AnnotationsType & get_type() const { return type; }
        AnnotationsType & get_mutable_type() { return type; }
        void set_type(const AnnotationsType & value) { this->type = value; }
    };

    class AdditionalPropertiesClass {
        public:
        AdditionalPropertiesClass() = default;
        virtual ~AdditionalPropertiesClass() = default;

        private:

        public:
    };

    class PurpleArguments {
        public:
        PurpleArguments() = default;
        virtual ~PurpleArguments() = default;

        private:
        AdditionalPropertiesClass additional_properties;
        AnnotationsType type;

        public:
        const AdditionalPropertiesClass & get_additional_properties() const { return additional_properties; }
        AdditionalPropertiesClass & get_mutable_additional_properties() { return additional_properties; }
        void set_additional_properties(const AdditionalPropertiesClass & value) { this->additional_properties = value; }

        const AnnotationsType & get_type() const { return type; }
        AnnotationsType & get_mutable_type() { return type; }
        void set_type(const AnnotationsType & value) { this->type = value; }
    };

    class Name {
        public:
        Name() = default;
        virtual ~Name() = default;

        private:
        TypeElement type;

        public:
        const TypeElement & get_type() const { return type; }
        TypeElement & get_mutable_type() { return type; }
        void set_type(const TypeElement & value) { this->type = value; }
    };

    class PurpleProperties {
        public:
        PurpleProperties() = default;
        virtual ~PurpleProperties() = default;

        private:
        PurpleArguments arguments;
        Name name;

        public:
        const PurpleArguments & get_arguments() const { return arguments; }
        PurpleArguments & get_mutable_arguments() { return arguments; }
        void set_arguments(const PurpleArguments & value) { this->arguments = value; }

        const Name & get_name() const { return name; }
        Name & get_mutable_name() { return name; }
        void set_name(const Name & value) { this->name = value; }
    };

    class PurpleParams {
        public:
        PurpleParams() = default;
        virtual ~PurpleParams() = default;

        private:
        PurpleProperties properties;
        std::vector<std::string> required;
        AnnotationsType type;

        public:
        const PurpleProperties & get_properties() const { return properties; }
        PurpleProperties & get_mutable_properties() { return properties; }
        void set_properties(const PurpleProperties & value) { this->properties = value; }

        const std::vector<std::string> & get_required() const { return required; }
        std::vector<std::string> & get_mutable_required() { return required; }
        void set_required(const std::vector<std::string> & value) { this->required = value; }

        const AnnotationsType & get_type() const { return type; }
        AnnotationsType & get_mutable_type() { return type; }
        void set_type(const AnnotationsType & value) { this->type = value; }
    };

    class CallToolRequestProperties {
        public:
        CallToolRequestProperties() = default;
        virtual ~CallToolRequestProperties() = default;

        private:
        TypeClass method;
        PurpleParams params;

        public:
        const TypeClass & get_method() const { return method; }
        TypeClass & get_mutable_method() { return method; }
        void set_method(const TypeClass & value) { this->method = value; }

        const PurpleParams & get_params() const { return params; }
        PurpleParams & get_mutable_params() { return params; }
        void set_params(const PurpleParams & value) { this->params = value; }
    };

    class CallToolRequest {
        public:
        CallToolRequest() = default;
        virtual ~CallToolRequest() = default;

        private:
        std::string description;
        CallToolRequestProperties properties;
        std::vector<std::string> required;
        AnnotationsType type;

        public:
        const std::string & get_description() const { return description; }
        std::string & get_mutable_description() { return description; }
        void set_description(const std::string & value) { this->description = value; }

        const CallToolRequestProperties & get_properties() const { return properties; }
        CallToolRequestProperties & get_mutable_properties() { return properties; }
        void set_properties(const CallToolRequestProperties & value) { this->properties = value; }

        const std::vector<std::string> & get_required() const { return required; }
        std::vector<std::string> & get_mutable_required() { return required; }
        void set_required(const std::vector<std::string> & value) { this->required = value; }

        const AnnotationsType & get_type() const { return type; }
        AnnotationsType & get_mutable_type() { return type; }
        void set_type(const AnnotationsType & value) { this->type = value; }
    };

    class ClientNotification {
        public:
        ClientNotification() = default;
        virtual ~ClientNotification() = default;

        private:
        std::vector<EmptyResult> any_of;

        public:
        const std::vector<EmptyResult> & get_any_of() const { return any_of; }
        std::vector<EmptyResult> & get_mutable_any_of() { return any_of; }
        void set_any_of(const std::vector<EmptyResult> & value) { this->any_of = value; }
    };

    class ContentClass {
        public:
        ContentClass() = default;
        virtual ~ContentClass() = default;

        private:
        ClientNotification items;
        std::string type;

        public:
        const ClientNotification & get_items() const { return items; }
        ClientNotification & get_mutable_items() { return items; }
        void set_items(const ClientNotification & value) { this->items = value; }

        const std::string & get_type() const { return type; }
        std::string & get_mutable_type() { return type; }
        void set_type(const std::string & value) { this->type = value; }
    };

    class PurpleMeta {
        public:
        PurpleMeta() = default;
        virtual ~PurpleMeta() = default;

        private:
        AdditionalPropertiesClass additional_properties;
        std::string description;
        AnnotationsType type;

        public:
        const AdditionalPropertiesClass & get_additional_properties() const { return additional_properties; }
        AdditionalPropertiesClass & get_mutable_additional_properties() { return additional_properties; }
        void set_additional_properties(const AdditionalPropertiesClass & value) { this->additional_properties = value; }

        const std::string & get_description() const { return description; }
        std::string & get_mutable_description() { return description; }
        void set_description(const std::string & value) { this->description = value; }

        const AnnotationsType & get_type() const { return type; }
        AnnotationsType & get_mutable_type() { return type; }
        void set_type(const AnnotationsType & value) { this->type = value; }
    };

    class CallToolResultProperties {
        public:
        CallToolResultProperties() = default;
        virtual ~CallToolResultProperties() = default;

        private:
        PurpleMeta meta;
        ContentClass content;
        Cursor is_error;

        public:
        const PurpleMeta & get_meta() const { return meta; }
        PurpleMeta & get_mutable_meta() { return meta; }
        void set_meta(const PurpleMeta & value) { this->meta = value; }

        const ContentClass & get_content() const { return content; }
        ContentClass & get_mutable_content() { return content; }
        void set_content(const ContentClass & value) { this->content = value; }

        const Cursor & get_is_error() const { return is_error; }
        Cursor & get_mutable_is_error() { return is_error; }
        void set_is_error(const Cursor & value) { this->is_error = value; }
    };

    class CallToolResult {
        public:
        CallToolResult() = default;
        virtual ~CallToolResult() = default;

        private:
        std::string description;
        CallToolResultProperties properties;
        std::vector<std::string> required;
        AnnotationsType type;

        public:
        const std::string & get_description() const { return description; }
        std::string & get_mutable_description() { return description; }
        void set_description(const std::string & value) { this->description = value; }

        const CallToolResultProperties & get_properties() const { return properties; }
        CallToolResultProperties & get_mutable_properties() { return properties; }
        void set_properties(const CallToolResultProperties & value) { this->properties = value; }

        const std::vector<std::string> & get_required() const { return required; }
        std::vector<std::string> & get_mutable_required() { return required; }
        void set_required(const std::vector<std::string> & value) { this->required = value; }

        const AnnotationsType & get_type() const { return type; }
        AnnotationsType & get_mutable_type() { return type; }
        void set_type(const AnnotationsType & value) { this->type = value; }
    };

    class FluffyProperties {
        public:
        FluffyProperties() = default;
        virtual ~FluffyProperties() = default;

        private:
        Cursor reason;
        AnnotationsClass request_id;

        public:
        const Cursor & get_reason() const { return reason; }
        Cursor & get_mutable_reason() { return reason; }
        void set_reason(const Cursor & value) { this->reason = value; }

        const AnnotationsClass & get_request_id() const { return request_id; }
        AnnotationsClass & get_mutable_request_id() { return request_id; }
        void set_request_id(const AnnotationsClass & value) { this->request_id = value; }
    };

    class FluffyParams {
        public:
        FluffyParams() = default;
        virtual ~FluffyParams() = default;

        private:
        FluffyProperties properties;
        std::vector<std::string> required;
        AnnotationsType type;

        public:
        const FluffyProperties & get_properties() const { return properties; }
        FluffyProperties & get_mutable_properties() { return properties; }
        void set_properties(const FluffyProperties & value) { this->properties = value; }

        const std::vector<std::string> & get_required() const { return required; }
        std::vector<std::string> & get_mutable_required() { return required; }
        void set_required(const std::vector<std::string> & value) { this->required = value; }

        const AnnotationsType & get_type() const { return type; }
        AnnotationsType & get_mutable_type() { return type; }
        void set_type(const AnnotationsType & value) { this->type = value; }
    };

    class CancelledNotificationProperties {
        public:
        CancelledNotificationProperties() = default;
        virtual ~CancelledNotificationProperties() = default;

        private:
        TypeClass method;
        FluffyParams params;

        public:
        const TypeClass & get_method() const { return method; }
        TypeClass & get_mutable_method() { return method; }
        void set_method(const TypeClass & value) { this->method = value; }

        const FluffyParams & get_params() const { return params; }
        FluffyParams & get_mutable_params() { return params; }
        void set_params(const FluffyParams & value) { this->params = value; }
    };

    class CancelledNotification {
        public:
        CancelledNotification() = default;
        virtual ~CancelledNotification() = default;

        private:
        std::string description;
        CancelledNotificationProperties properties;
        std::vector<std::string> required;
        AnnotationsType type;

        public:
        const std::string & get_description() const { return description; }
        std::string & get_mutable_description() { return description; }
        void set_description(const std::string & value) { this->description = value; }

        const CancelledNotificationProperties & get_properties() const { return properties; }
        CancelledNotificationProperties & get_mutable_properties() { return properties; }
        void set_properties(const CancelledNotificationProperties & value) { this->properties = value; }

        const std::vector<std::string> & get_required() const { return required; }
        std::vector<std::string> & get_mutable_required() { return required; }
        void set_required(const std::vector<std::string> & value) { this->required = value; }

        const AnnotationsType & get_type() const { return type; }
        AnnotationsType & get_mutable_type() { return type; }
        void set_type(const AnnotationsType & value) { this->type = value; }
    };

    class Sampling {
        public:
        Sampling() = default;
        virtual ~Sampling() = default;

        private:
        bool additional_properties;
        AdditionalPropertiesClass properties;
        AnnotationsType type;
        boost::optional<std::string> description;

        public:
        const bool & get_additional_properties() const { return additional_properties; }
        bool & get_mutable_additional_properties() { return additional_properties; }
        void set_additional_properties(const bool & value) { this->additional_properties = value; }

        const AdditionalPropertiesClass & get_properties() const { return properties; }
        AdditionalPropertiesClass & get_mutable_properties() { return properties; }
        void set_properties(const AdditionalPropertiesClass & value) { this->properties = value; }

        const AnnotationsType & get_type() const { return type; }
        AnnotationsType & get_mutable_type() { return type; }
        void set_type(const AnnotationsType & value) { this->type = value; }

        boost::optional<std::string> get_description() const { return description; }
        void set_description(boost::optional<std::string> value) { this->description = value; }
    };

    class Experimental {
        public:
        Experimental() = default;
        virtual ~Experimental() = default;

        private:
        Sampling additional_properties;
        std::string description;
        AnnotationsType type;

        public:
        const Sampling & get_additional_properties() const { return additional_properties; }
        Sampling & get_mutable_additional_properties() { return additional_properties; }
        void set_additional_properties(const Sampling & value) { this->additional_properties = value; }

        const std::string & get_description() const { return description; }
        std::string & get_mutable_description() { return description; }
        void set_description(const std::string & value) { this->description = value; }

        const AnnotationsType & get_type() const { return type; }
        AnnotationsType & get_mutable_type() { return type; }
        void set_type(const AnnotationsType & value) { this->type = value; }
    };

    class RootsProperties {
        public:
        RootsProperties() = default;
        virtual ~RootsProperties() = default;

        private:
        Cursor list_changed;

        public:
        const Cursor & get_list_changed() const { return list_changed; }
        Cursor & get_mutable_list_changed() { return list_changed; }
        void set_list_changed(const Cursor & value) { this->list_changed = value; }
    };

    class Roots {
        public:
        Roots() = default;
        virtual ~Roots() = default;

        private:
        std::string description;
        RootsProperties properties;
        AnnotationsType type;

        public:
        const std::string & get_description() const { return description; }
        std::string & get_mutable_description() { return description; }
        void set_description(const std::string & value) { this->description = value; }

        const RootsProperties & get_properties() const { return properties; }
        RootsProperties & get_mutable_properties() { return properties; }
        void set_properties(const RootsProperties & value) { this->properties = value; }

        const AnnotationsType & get_type() const { return type; }
        AnnotationsType & get_mutable_type() { return type; }
        void set_type(const AnnotationsType & value) { this->type = value; }
    };

    class ClientCapabilitiesProperties {
        public:
        ClientCapabilitiesProperties() = default;
        virtual ~ClientCapabilitiesProperties() = default;

        private:
        Experimental experimental;
        Roots roots;
        Sampling sampling;

        public:
        const Experimental & get_experimental() const { return experimental; }
        Experimental & get_mutable_experimental() { return experimental; }
        void set_experimental(const Experimental & value) { this->experimental = value; }

        const Roots & get_roots() const { return roots; }
        Roots & get_mutable_roots() { return roots; }
        void set_roots(const Roots & value) { this->roots = value; }

        const Sampling & get_sampling() const { return sampling; }
        Sampling & get_mutable_sampling() { return sampling; }
        void set_sampling(const Sampling & value) { this->sampling = value; }
    };

    class ClientCapabilities {
        public:
        ClientCapabilities() = default;
        virtual ~ClientCapabilities() = default;

        private:
        std::string description;
        ClientCapabilitiesProperties properties;
        AnnotationsType type;

        public:
        const std::string & get_description() const { return description; }
        std::string & get_mutable_description() { return description; }
        void set_description(const std::string & value) { this->description = value; }

        const ClientCapabilitiesProperties & get_properties() const { return properties; }
        ClientCapabilitiesProperties & get_mutable_properties() { return properties; }
        void set_properties(const ClientCapabilitiesProperties & value) { this->properties = value; }

        const AnnotationsType & get_type() const { return type; }
        AnnotationsType & get_mutable_type() { return type; }
        void set_type(const AnnotationsType & value) { this->type = value; }
    };

    class ArgumentProperties {
        public:
        ArgumentProperties() = default;
        virtual ~ArgumentProperties() = default;

        private:
        Cursor name;
        Cursor value;

        public:
        const Cursor & get_name() const { return name; }
        Cursor & get_mutable_name() { return name; }
        void set_name(const Cursor & value) { this->name = value; }

        const Cursor & get_value() const { return value; }
        Cursor & get_mutable_value() { return value; }
        void set_value(const Cursor & value) { this->value = value; }
    };

    class Argument {
        public:
        Argument() = default;
        virtual ~Argument() = default;

        private:
        std::string description;
        ArgumentProperties properties;
        std::vector<std::string> required;
        AnnotationsType type;

        public:
        const std::string & get_description() const { return description; }
        std::string & get_mutable_description() { return description; }
        void set_description(const std::string & value) { this->description = value; }

        const ArgumentProperties & get_properties() const { return properties; }
        ArgumentProperties & get_mutable_properties() { return properties; }
        void set_properties(const ArgumentProperties & value) { this->properties = value; }

        const std::vector<std::string> & get_required() const { return required; }
        std::vector<std::string> & get_mutable_required() { return required; }
        void set_required(const std::vector<std::string> & value) { this->required = value; }

        const AnnotationsType & get_type() const { return type; }
        AnnotationsType & get_mutable_type() { return type; }
        void set_type(const AnnotationsType & value) { this->type = value; }
    };

    class TentacledProperties {
        public:
        TentacledProperties() = default;
        virtual ~TentacledProperties() = default;

        private:
        Argument argument;
        ClientNotification ref;

        public:
        const Argument & get_argument() const { return argument; }
        Argument & get_mutable_argument() { return argument; }
        void set_argument(const Argument & value) { this->argument = value; }

        const ClientNotification & get_ref() const { return ref; }
        ClientNotification & get_mutable_ref() { return ref; }
        void set_ref(const ClientNotification & value) { this->ref = value; }
    };

    class TentacledParams {
        public:
        TentacledParams() = default;
        virtual ~TentacledParams() = default;

        private:
        TentacledProperties properties;
        std::vector<std::string> required;
        AnnotationsType type;

        public:
        const TentacledProperties & get_properties() const { return properties; }
        TentacledProperties & get_mutable_properties() { return properties; }
        void set_properties(const TentacledProperties & value) { this->properties = value; }

        const std::vector<std::string> & get_required() const { return required; }
        std::vector<std::string> & get_mutable_required() { return required; }
        void set_required(const std::vector<std::string> & value) { this->required = value; }

        const AnnotationsType & get_type() const { return type; }
        AnnotationsType & get_mutable_type() { return type; }
        void set_type(const AnnotationsType & value) { this->type = value; }
    };

    class CompleteRequestProperties {
        public:
        CompleteRequestProperties() = default;
        virtual ~CompleteRequestProperties() = default;

        private:
        TypeClass method;
        TentacledParams params;

        public:
        const TypeClass & get_method() const { return method; }
        TypeClass & get_mutable_method() { return method; }
        void set_method(const TypeClass & value) { this->method = value; }

        const TentacledParams & get_params() const { return params; }
        TentacledParams & get_mutable_params() { return params; }
        void set_params(const TentacledParams & value) { this->params = value; }
    };

    class CompleteRequest {
        public:
        CompleteRequest() = default;
        virtual ~CompleteRequest() = default;

        private:
        std::string description;
        CompleteRequestProperties properties;
        std::vector<std::string> required;
        AnnotationsType type;

        public:
        const std::string & get_description() const { return description; }
        std::string & get_mutable_description() { return description; }
        void set_description(const std::string & value) { this->description = value; }

        const CompleteRequestProperties & get_properties() const { return properties; }
        CompleteRequestProperties & get_mutable_properties() { return properties; }
        void set_properties(const CompleteRequestProperties & value) { this->properties = value; }

        const std::vector<std::string> & get_required() const { return required; }
        std::vector<std::string> & get_mutable_required() { return required; }
        void set_required(const std::vector<std::string> & value) { this->required = value; }

        const AnnotationsType & get_type() const { return type; }
        AnnotationsType & get_mutable_type() { return type; }
        void set_type(const AnnotationsType & value) { this->type = value; }
    };

    class Values {
        public:
        Values() = default;
        virtual ~Values() = default;

        private:
        std::string description;
        Name items;
        std::string type;

        public:
        const std::string & get_description() const { return description; }
        std::string & get_mutable_description() { return description; }
        void set_description(const std::string & value) { this->description = value; }

        const Name & get_items() const { return items; }
        Name & get_mutable_items() { return items; }
        void set_items(const Name & value) { this->items = value; }

        const std::string & get_type() const { return type; }
        std::string & get_mutable_type() { return type; }
        void set_type(const std::string & value) { this->type = value; }
    };

    class CompletionProperties {
        public:
        CompletionProperties() = default;
        virtual ~CompletionProperties() = default;

        private:
        Cursor has_more;
        Cursor total;
        Values values;

        public:
        const Cursor & get_has_more() const { return has_more; }
        Cursor & get_mutable_has_more() { return has_more; }
        void set_has_more(const Cursor & value) { this->has_more = value; }

        const Cursor & get_total() const { return total; }
        Cursor & get_mutable_total() { return total; }
        void set_total(const Cursor & value) { this->total = value; }

        const Values & get_values() const { return values; }
        Values & get_mutable_values() { return values; }
        void set_values(const Values & value) { this->values = value; }
    };

    class Completion {
        public:
        Completion() = default;
        virtual ~Completion() = default;

        private:
        CompletionProperties properties;
        std::vector<std::string> required;
        AnnotationsType type;

        public:
        const CompletionProperties & get_properties() const { return properties; }
        CompletionProperties & get_mutable_properties() { return properties; }
        void set_properties(const CompletionProperties & value) { this->properties = value; }

        const std::vector<std::string> & get_required() const { return required; }
        std::vector<std::string> & get_mutable_required() { return required; }
        void set_required(const std::vector<std::string> & value) { this->required = value; }

        const AnnotationsType & get_type() const { return type; }
        AnnotationsType & get_mutable_type() { return type; }
        void set_type(const AnnotationsType & value) { this->type = value; }
    };

    class CompleteResultProperties {
        public:
        CompleteResultProperties() = default;
        virtual ~CompleteResultProperties() = default;

        private:
        PurpleMeta meta;
        Completion completion;

        public:
        const PurpleMeta & get_meta() const { return meta; }
        PurpleMeta & get_mutable_meta() { return meta; }
        void set_meta(const PurpleMeta & value) { this->meta = value; }

        const Completion & get_completion() const { return completion; }
        Completion & get_mutable_completion() { return completion; }
        void set_completion(const Completion & value) { this->completion = value; }
    };

    class CompleteResult {
        public:
        CompleteResult() = default;
        virtual ~CompleteResult() = default;

        private:
        std::string description;
        CompleteResultProperties properties;
        std::vector<std::string> required;
        AnnotationsType type;

        public:
        const std::string & get_description() const { return description; }
        std::string & get_mutable_description() { return description; }
        void set_description(const std::string & value) { this->description = value; }

        const CompleteResultProperties & get_properties() const { return properties; }
        CompleteResultProperties & get_mutable_properties() { return properties; }
        void set_properties(const CompleteResultProperties & value) { this->properties = value; }

        const std::vector<std::string> & get_required() const { return required; }
        std::vector<std::string> & get_mutable_required() { return required; }
        void set_required(const std::vector<std::string> & value) { this->required = value; }

        const AnnotationsType & get_type() const { return type; }
        AnnotationsType & get_mutable_type() { return type; }
        void set_type(const AnnotationsType & value) { this->type = value; }
    };

    class LoggingLevel {
        public:
        LoggingLevel() = default;
        virtual ~LoggingLevel() = default;

        private:
        std::string description;
        std::vector<std::string> logging_level_enum;
        TypeElement type;

        public:
        const std::string & get_description() const { return description; }
        std::string & get_mutable_description() { return description; }
        void set_description(const std::string & value) { this->description = value; }

        const std::vector<std::string> & get_logging_level_enum() const { return logging_level_enum; }
        std::vector<std::string> & get_mutable_logging_level_enum() { return logging_level_enum; }
        void set_logging_level_enum(const std::vector<std::string> & value) { this->logging_level_enum = value; }

        const TypeElement & get_type() const { return type; }
        TypeElement & get_mutable_type() { return type; }
        void set_type(const TypeElement & value) { this->type = value; }
    };

    class Messages {
        public:
        Messages() = default;
        virtual ~Messages() = default;

        private:
        EmptyResult items;
        std::string type;

        public:
        const EmptyResult & get_items() const { return items; }
        EmptyResult & get_mutable_items() { return items; }
        void set_items(const EmptyResult & value) { this->items = value; }

        const std::string & get_type() const { return type; }
        std::string & get_mutable_type() { return type; }
        void set_type(const std::string & value) { this->type = value; }
    };

    class StopSequences {
        public:
        StopSequences() = default;
        virtual ~StopSequences() = default;

        private:
        Name items;
        std::string type;

        public:
        const Name & get_items() const { return items; }
        Name & get_mutable_items() { return items; }
        void set_items(const Name & value) { this->items = value; }

        const std::string & get_type() const { return type; }
        std::string & get_mutable_type() { return type; }
        void set_type(const std::string & value) { this->type = value; }
    };

    class StickyProperties {
        public:
        StickyProperties() = default;
        virtual ~StickyProperties() = default;

        private:
        LoggingLevel include_context;
        Cursor max_tokens;
        Messages messages;
        Sampling metadata;
        AnnotationsClass model_preferences;
        StopSequences stop_sequences;
        Cursor system_prompt;
        Name temperature;

        public:
        const LoggingLevel & get_include_context() const { return include_context; }
        LoggingLevel & get_mutable_include_context() { return include_context; }
        void set_include_context(const LoggingLevel & value) { this->include_context = value; }

        const Cursor & get_max_tokens() const { return max_tokens; }
        Cursor & get_mutable_max_tokens() { return max_tokens; }
        void set_max_tokens(const Cursor & value) { this->max_tokens = value; }

        const Messages & get_messages() const { return messages; }
        Messages & get_mutable_messages() { return messages; }
        void set_messages(const Messages & value) { this->messages = value; }

        const Sampling & get_metadata() const { return metadata; }
        Sampling & get_mutable_metadata() { return metadata; }
        void set_metadata(const Sampling & value) { this->metadata = value; }

        const AnnotationsClass & get_model_preferences() const { return model_preferences; }
        AnnotationsClass & get_mutable_model_preferences() { return model_preferences; }
        void set_model_preferences(const AnnotationsClass & value) { this->model_preferences = value; }

        const StopSequences & get_stop_sequences() const { return stop_sequences; }
        StopSequences & get_mutable_stop_sequences() { return stop_sequences; }
        void set_stop_sequences(const StopSequences & value) { this->stop_sequences = value; }

        const Cursor & get_system_prompt() const { return system_prompt; }
        Cursor & get_mutable_system_prompt() { return system_prompt; }
        void set_system_prompt(const Cursor & value) { this->system_prompt = value; }

        const Name & get_temperature() const { return temperature; }
        Name & get_mutable_temperature() { return temperature; }
        void set_temperature(const Name & value) { this->temperature = value; }
    };

    class StickyParams {
        public:
        StickyParams() = default;
        virtual ~StickyParams() = default;

        private:
        StickyProperties properties;
        std::vector<std::string> required;
        AnnotationsType type;

        public:
        const StickyProperties & get_properties() const { return properties; }
        StickyProperties & get_mutable_properties() { return properties; }
        void set_properties(const StickyProperties & value) { this->properties = value; }

        const std::vector<std::string> & get_required() const { return required; }
        std::vector<std::string> & get_mutable_required() { return required; }
        void set_required(const std::vector<std::string> & value) { this->required = value; }

        const AnnotationsType & get_type() const { return type; }
        AnnotationsType & get_mutable_type() { return type; }
        void set_type(const AnnotationsType & value) { this->type = value; }
    };

    class CreateMessageRequestProperties {
        public:
        CreateMessageRequestProperties() = default;
        virtual ~CreateMessageRequestProperties() = default;

        private:
        TypeClass method;
        StickyParams params;

        public:
        const TypeClass & get_method() const { return method; }
        TypeClass & get_mutable_method() { return method; }
        void set_method(const TypeClass & value) { this->method = value; }

        const StickyParams & get_params() const { return params; }
        StickyParams & get_mutable_params() { return params; }
        void set_params(const StickyParams & value) { this->params = value; }
    };

    class CreateMessageRequest {
        public:
        CreateMessageRequest() = default;
        virtual ~CreateMessageRequest() = default;

        private:
        std::string description;
        CreateMessageRequestProperties properties;
        std::vector<std::string> required;
        AnnotationsType type;

        public:
        const std::string & get_description() const { return description; }
        std::string & get_mutable_description() { return description; }
        void set_description(const std::string & value) { this->description = value; }

        const CreateMessageRequestProperties & get_properties() const { return properties; }
        CreateMessageRequestProperties & get_mutable_properties() { return properties; }
        void set_properties(const CreateMessageRequestProperties & value) { this->properties = value; }

        const std::vector<std::string> & get_required() const { return required; }
        std::vector<std::string> & get_mutable_required() { return required; }
        void set_required(const std::vector<std::string> & value) { this->required = value; }

        const AnnotationsType & get_type() const { return type; }
        AnnotationsType & get_mutable_type() { return type; }
        void set_type(const AnnotationsType & value) { this->type = value; }
    };

    class CreateMessageResultProperties {
        public:
        CreateMessageResultProperties() = default;
        virtual ~CreateMessageResultProperties() = default;

        private:
        PurpleMeta meta;
        ClientNotification content;
        Cursor model;
        EmptyResult role;
        Cursor stop_reason;

        public:
        const PurpleMeta & get_meta() const { return meta; }
        PurpleMeta & get_mutable_meta() { return meta; }
        void set_meta(const PurpleMeta & value) { this->meta = value; }

        const ClientNotification & get_content() const { return content; }
        ClientNotification & get_mutable_content() { return content; }
        void set_content(const ClientNotification & value) { this->content = value; }

        const Cursor & get_model() const { return model; }
        Cursor & get_mutable_model() { return model; }
        void set_model(const Cursor & value) { this->model = value; }

        const EmptyResult & get_role() const { return role; }
        EmptyResult & get_mutable_role() { return role; }
        void set_role(const EmptyResult & value) { this->role = value; }

        const Cursor & get_stop_reason() const { return stop_reason; }
        Cursor & get_mutable_stop_reason() { return stop_reason; }
        void set_stop_reason(const Cursor & value) { this->stop_reason = value; }
    };

    class CreateMessageResult {
        public:
        CreateMessageResult() = default;
        virtual ~CreateMessageResult() = default;

        private:
        std::string description;
        CreateMessageResultProperties properties;
        std::vector<std::string> required;
        AnnotationsType type;

        public:
        const std::string & get_description() const { return description; }
        std::string & get_mutable_description() { return description; }
        void set_description(const std::string & value) { this->description = value; }

        const CreateMessageResultProperties & get_properties() const { return properties; }
        CreateMessageResultProperties & get_mutable_properties() { return properties; }
        void set_properties(const CreateMessageResultProperties & value) { this->properties = value; }

        const std::vector<std::string> & get_required() const { return required; }
        std::vector<std::string> & get_mutable_required() { return required; }
        void set_required(const std::vector<std::string> & value) { this->required = value; }

        const AnnotationsType & get_type() const { return type; }
        AnnotationsType & get_mutable_type() { return type; }
        void set_type(const AnnotationsType & value) { this->type = value; }
    };

    class EmbeddedResourceProperties {
        public:
        EmbeddedResourceProperties() = default;
        virtual ~EmbeddedResourceProperties() = default;

        private:
        AnnotationsClass annotations;
        ClientNotification resource;
        TypeClass type;

        public:
        const AnnotationsClass & get_annotations() const { return annotations; }
        AnnotationsClass & get_mutable_annotations() { return annotations; }
        void set_annotations(const AnnotationsClass & value) { this->annotations = value; }

        const ClientNotification & get_resource() const { return resource; }
        ClientNotification & get_mutable_resource() { return resource; }
        void set_resource(const ClientNotification & value) { this->resource = value; }

        const TypeClass & get_type() const { return type; }
        TypeClass & get_mutable_type() { return type; }
        void set_type(const TypeClass & value) { this->type = value; }
    };

    class EmbeddedResource {
        public:
        EmbeddedResource() = default;
        virtual ~EmbeddedResource() = default;

        private:
        std::string description;
        EmbeddedResourceProperties properties;
        std::vector<std::string> required;
        AnnotationsType type;

        public:
        const std::string & get_description() const { return description; }
        std::string & get_mutable_description() { return description; }
        void set_description(const std::string & value) { this->description = value; }

        const EmbeddedResourceProperties & get_properties() const { return properties; }
        EmbeddedResourceProperties & get_mutable_properties() { return properties; }
        void set_properties(const EmbeddedResourceProperties & value) { this->properties = value; }

        const std::vector<std::string> & get_required() const { return required; }
        std::vector<std::string> & get_mutable_required() { return required; }
        void set_required(const std::vector<std::string> & value) { this->required = value; }

        const AnnotationsType & get_type() const { return type; }
        AnnotationsType & get_mutable_type() { return type; }
        void set_type(const AnnotationsType & value) { this->type = value; }
    };

    class FluffyArguments {
        public:
        FluffyArguments() = default;
        virtual ~FluffyArguments() = default;

        private:
        Name additional_properties;
        std::string description;
        AnnotationsType type;

        public:
        const Name & get_additional_properties() const { return additional_properties; }
        Name & get_mutable_additional_properties() { return additional_properties; }
        void set_additional_properties(const Name & value) { this->additional_properties = value; }

        const std::string & get_description() const { return description; }
        std::string & get_mutable_description() { return description; }
        void set_description(const std::string & value) { this->description = value; }

        const AnnotationsType & get_type() const { return type; }
        AnnotationsType & get_mutable_type() { return type; }
        void set_type(const AnnotationsType & value) { this->type = value; }
    };

    class IndigoProperties {
        public:
        IndigoProperties() = default;
        virtual ~IndigoProperties() = default;

        private:
        FluffyArguments arguments;
        Cursor name;

        public:
        const FluffyArguments & get_arguments() const { return arguments; }
        FluffyArguments & get_mutable_arguments() { return arguments; }
        void set_arguments(const FluffyArguments & value) { this->arguments = value; }

        const Cursor & get_name() const { return name; }
        Cursor & get_mutable_name() { return name; }
        void set_name(const Cursor & value) { this->name = value; }
    };

    class IndigoParams {
        public:
        IndigoParams() = default;
        virtual ~IndigoParams() = default;

        private:
        IndigoProperties properties;
        std::vector<std::string> required;
        AnnotationsType type;

        public:
        const IndigoProperties & get_properties() const { return properties; }
        IndigoProperties & get_mutable_properties() { return properties; }
        void set_properties(const IndigoProperties & value) { this->properties = value; }

        const std::vector<std::string> & get_required() const { return required; }
        std::vector<std::string> & get_mutable_required() { return required; }
        void set_required(const std::vector<std::string> & value) { this->required = value; }

        const AnnotationsType & get_type() const { return type; }
        AnnotationsType & get_mutable_type() { return type; }
        void set_type(const AnnotationsType & value) { this->type = value; }
    };

    class GetPromptRequestProperties {
        public:
        GetPromptRequestProperties() = default;
        virtual ~GetPromptRequestProperties() = default;

        private:
        TypeClass method;
        IndigoParams params;

        public:
        const TypeClass & get_method() const { return method; }
        TypeClass & get_mutable_method() { return method; }
        void set_method(const TypeClass & value) { this->method = value; }

        const IndigoParams & get_params() const { return params; }
        IndigoParams & get_mutable_params() { return params; }
        void set_params(const IndigoParams & value) { this->params = value; }
    };

    class GetPromptRequest {
        public:
        GetPromptRequest() = default;
        virtual ~GetPromptRequest() = default;

        private:
        std::string description;
        GetPromptRequestProperties properties;
        std::vector<std::string> required;
        AnnotationsType type;

        public:
        const std::string & get_description() const { return description; }
        std::string & get_mutable_description() { return description; }
        void set_description(const std::string & value) { this->description = value; }

        const GetPromptRequestProperties & get_properties() const { return properties; }
        GetPromptRequestProperties & get_mutable_properties() { return properties; }
        void set_properties(const GetPromptRequestProperties & value) { this->properties = value; }

        const std::vector<std::string> & get_required() const { return required; }
        std::vector<std::string> & get_mutable_required() { return required; }
        void set_required(const std::vector<std::string> & value) { this->required = value; }

        const AnnotationsType & get_type() const { return type; }
        AnnotationsType & get_mutable_type() { return type; }
        void set_type(const AnnotationsType & value) { this->type = value; }
    };

    class GetPromptResultProperties {
        public:
        GetPromptResultProperties() = default;
        virtual ~GetPromptResultProperties() = default;

        private:
        PurpleMeta meta;
        Cursor description;
        Messages messages;

        public:
        const PurpleMeta & get_meta() const { return meta; }
        PurpleMeta & get_mutable_meta() { return meta; }
        void set_meta(const PurpleMeta & value) { this->meta = value; }

        const Cursor & get_description() const { return description; }
        Cursor & get_mutable_description() { return description; }
        void set_description(const Cursor & value) { this->description = value; }

        const Messages & get_messages() const { return messages; }
        Messages & get_mutable_messages() { return messages; }
        void set_messages(const Messages & value) { this->messages = value; }
    };

    class GetPromptResult {
        public:
        GetPromptResult() = default;
        virtual ~GetPromptResult() = default;

        private:
        std::string description;
        GetPromptResultProperties properties;
        std::vector<std::string> required;
        AnnotationsType type;

        public:
        const std::string & get_description() const { return description; }
        std::string & get_mutable_description() { return description; }
        void set_description(const std::string & value) { this->description = value; }

        const GetPromptResultProperties & get_properties() const { return properties; }
        GetPromptResultProperties & get_mutable_properties() { return properties; }
        void set_properties(const GetPromptResultProperties & value) { this->properties = value; }

        const std::vector<std::string> & get_required() const { return required; }
        std::vector<std::string> & get_mutable_required() { return required; }
        void set_required(const std::vector<std::string> & value) { this->required = value; }

        const AnnotationsType & get_type() const { return type; }
        AnnotationsType & get_mutable_type() { return type; }
        void set_type(const AnnotationsType & value) { this->type = value; }
    };

    class ImplementationProperties {
        public:
        ImplementationProperties() = default;
        virtual ~ImplementationProperties() = default;

        private:
        Name name;
        Name version;

        public:
        const Name & get_name() const { return name; }
        Name & get_mutable_name() { return name; }
        void set_name(const Name & value) { this->name = value; }

        const Name & get_version() const { return version; }
        Name & get_mutable_version() { return version; }
        void set_version(const Name & value) { this->version = value; }
    };

    class Implementation {
        public:
        Implementation() = default;
        virtual ~Implementation() = default;

        private:
        std::string description;
        ImplementationProperties properties;
        std::vector<std::string> required;
        AnnotationsType type;

        public:
        const std::string & get_description() const { return description; }
        std::string & get_mutable_description() { return description; }
        void set_description(const std::string & value) { this->description = value; }

        const ImplementationProperties & get_properties() const { return properties; }
        ImplementationProperties & get_mutable_properties() { return properties; }
        void set_properties(const ImplementationProperties & value) { this->properties = value; }

        const std::vector<std::string> & get_required() const { return required; }
        std::vector<std::string> & get_mutable_required() { return required; }
        void set_required(const std::vector<std::string> & value) { this->required = value; }

        const AnnotationsType & get_type() const { return type; }
        AnnotationsType & get_mutable_type() { return type; }
        void set_type(const AnnotationsType & value) { this->type = value; }
    };

    class IndecentProperties {
        public:
        IndecentProperties() = default;
        virtual ~IndecentProperties() = default;

        private:
        EmptyResult capabilities;
        EmptyResult client_info;
        Cursor protocol_version;

        public:
        const EmptyResult & get_capabilities() const { return capabilities; }
        EmptyResult & get_mutable_capabilities() { return capabilities; }
        void set_capabilities(const EmptyResult & value) { this->capabilities = value; }

        const EmptyResult & get_client_info() const { return client_info; }
        EmptyResult & get_mutable_client_info() { return client_info; }
        void set_client_info(const EmptyResult & value) { this->client_info = value; }

        const Cursor & get_protocol_version() const { return protocol_version; }
        Cursor & get_mutable_protocol_version() { return protocol_version; }
        void set_protocol_version(const Cursor & value) { this->protocol_version = value; }
    };

    class IndecentParams {
        public:
        IndecentParams() = default;
        virtual ~IndecentParams() = default;

        private:
        IndecentProperties properties;
        std::vector<std::string> required;
        AnnotationsType type;

        public:
        const IndecentProperties & get_properties() const { return properties; }
        IndecentProperties & get_mutable_properties() { return properties; }
        void set_properties(const IndecentProperties & value) { this->properties = value; }

        const std::vector<std::string> & get_required() const { return required; }
        std::vector<std::string> & get_mutable_required() { return required; }
        void set_required(const std::vector<std::string> & value) { this->required = value; }

        const AnnotationsType & get_type() const { return type; }
        AnnotationsType & get_mutable_type() { return type; }
        void set_type(const AnnotationsType & value) { this->type = value; }
    };

    class InitializeRequestProperties {
        public:
        InitializeRequestProperties() = default;
        virtual ~InitializeRequestProperties() = default;

        private:
        TypeClass method;
        IndecentParams params;

        public:
        const TypeClass & get_method() const { return method; }
        TypeClass & get_mutable_method() { return method; }
        void set_method(const TypeClass & value) { this->method = value; }

        const IndecentParams & get_params() const { return params; }
        IndecentParams & get_mutable_params() { return params; }
        void set_params(const IndecentParams & value) { this->params = value; }
    };

    class InitializeRequest {
        public:
        InitializeRequest() = default;
        virtual ~InitializeRequest() = default;

        private:
        std::string description;
        InitializeRequestProperties properties;
        std::vector<std::string> required;
        AnnotationsType type;

        public:
        const std::string & get_description() const { return description; }
        std::string & get_mutable_description() { return description; }
        void set_description(const std::string & value) { this->description = value; }

        const InitializeRequestProperties & get_properties() const { return properties; }
        InitializeRequestProperties & get_mutable_properties() { return properties; }
        void set_properties(const InitializeRequestProperties & value) { this->properties = value; }

        const std::vector<std::string> & get_required() const { return required; }
        std::vector<std::string> & get_mutable_required() { return required; }
        void set_required(const std::vector<std::string> & value) { this->required = value; }

        const AnnotationsType & get_type() const { return type; }
        AnnotationsType & get_mutable_type() { return type; }
        void set_type(const AnnotationsType & value) { this->type = value; }
    };

    class InitializeResultProperties {
        public:
        InitializeResultProperties() = default;
        virtual ~InitializeResultProperties() = default;

        private:
        PurpleMeta meta;
        EmptyResult capabilities;
        Cursor instructions;
        Cursor protocol_version;
        EmptyResult server_info;

        public:
        const PurpleMeta & get_meta() const { return meta; }
        PurpleMeta & get_mutable_meta() { return meta; }
        void set_meta(const PurpleMeta & value) { this->meta = value; }

        const EmptyResult & get_capabilities() const { return capabilities; }
        EmptyResult & get_mutable_capabilities() { return capabilities; }
        void set_capabilities(const EmptyResult & value) { this->capabilities = value; }

        const Cursor & get_instructions() const { return instructions; }
        Cursor & get_mutable_instructions() { return instructions; }
        void set_instructions(const Cursor & value) { this->instructions = value; }

        const Cursor & get_protocol_version() const { return protocol_version; }
        Cursor & get_mutable_protocol_version() { return protocol_version; }
        void set_protocol_version(const Cursor & value) { this->protocol_version = value; }

        const EmptyResult & get_server_info() const { return server_info; }
        EmptyResult & get_mutable_server_info() { return server_info; }
        void set_server_info(const EmptyResult & value) { this->server_info = value; }
    };

    class InitializeResult {
        public:
        InitializeResult() = default;
        virtual ~InitializeResult() = default;

        private:
        std::string description;
        InitializeResultProperties properties;
        std::vector<std::string> required;
        AnnotationsType type;

        public:
        const std::string & get_description() const { return description; }
        std::string & get_mutable_description() { return description; }
        void set_description(const std::string & value) { this->description = value; }

        const InitializeResultProperties & get_properties() const { return properties; }
        InitializeResultProperties & get_mutable_properties() { return properties; }
        void set_properties(const InitializeResultProperties & value) { this->properties = value; }

        const std::vector<std::string> & get_required() const { return required; }
        std::vector<std::string> & get_mutable_required() { return required; }
        void set_required(const std::vector<std::string> & value) { this->required = value; }

        const AnnotationsType & get_type() const { return type; }
        AnnotationsType & get_mutable_type() { return type; }
        void set_type(const AnnotationsType & value) { this->type = value; }
    };

    class HilariousProperties {
        public:
        HilariousProperties() = default;
        virtual ~HilariousProperties() = default;

        private:
        PurpleMeta meta;

        public:
        const PurpleMeta & get_meta() const { return meta; }
        PurpleMeta & get_mutable_meta() { return meta; }
        void set_meta(const PurpleMeta & value) { this->meta = value; }
    };

    class Result {
        public:
        Result() = default;
        virtual ~Result() = default;

        private:
        AdditionalPropertiesClass additional_properties;
        HilariousProperties properties;
        AnnotationsType type;

        public:
        const AdditionalPropertiesClass & get_additional_properties() const { return additional_properties; }
        AdditionalPropertiesClass & get_mutable_additional_properties() { return additional_properties; }
        void set_additional_properties(const AdditionalPropertiesClass & value) { this->additional_properties = value; }

        const HilariousProperties & get_properties() const { return properties; }
        HilariousProperties & get_mutable_properties() { return properties; }
        void set_properties(const HilariousProperties & value) { this->properties = value; }

        const AnnotationsType & get_type() const { return type; }
        AnnotationsType & get_mutable_type() { return type; }
        void set_type(const AnnotationsType & value) { this->type = value; }
    };

    class InitializedNotificationProperties {
        public:
        InitializedNotificationProperties() = default;
        virtual ~InitializedNotificationProperties() = default;

        private:
        TypeClass method;
        Result params;

        public:
        const TypeClass & get_method() const { return method; }
        TypeClass & get_mutable_method() { return method; }
        void set_method(const TypeClass & value) { this->method = value; }

        const Result & get_params() const { return params; }
        Result & get_mutable_params() { return params; }
        void set_params(const Result & value) { this->params = value; }
    };

    class EdNotification {
        public:
        EdNotification() = default;
        virtual ~EdNotification() = default;

        private:
        std::string description;
        InitializedNotificationProperties properties;
        std::vector<std::string> required;
        AnnotationsType type;

        public:
        const std::string & get_description() const { return description; }
        std::string & get_mutable_description() { return description; }
        void set_description(const std::string & value) { this->description = value; }

        const InitializedNotificationProperties & get_properties() const { return properties; }
        InitializedNotificationProperties & get_mutable_properties() { return properties; }
        void set_properties(const InitializedNotificationProperties & value) { this->properties = value; }

        const std::vector<std::string> & get_required() const { return required; }
        std::vector<std::string> & get_mutable_required() { return required; }
        void set_required(const std::vector<std::string> & value) { this->required = value; }

        const AnnotationsType & get_type() const { return type; }
        AnnotationsType & get_mutable_type() { return type; }
        void set_type(const AnnotationsType & value) { this->type = value; }
    };

    class JsonrpcBatchRequest {
        public:
        JsonrpcBatchRequest() = default;
        virtual ~JsonrpcBatchRequest() = default;

        private:
        boost::optional<std::string> description;
        boost::optional<ClientNotification> items;
        boost::optional<std::string> type;
        boost::optional<std::string> ref;

        public:
        boost::optional<std::string> get_description() const { return description; }
        void set_description(boost::optional<std::string> value) { this->description = value; }

        boost::optional<ClientNotification> get_items() const { return items; }
        void set_items(boost::optional<ClientNotification> value) { this->items = value; }

        boost::optional<std::string> get_type() const { return type; }
        void set_type(boost::optional<std::string> value) { this->type = value; }

        boost::optional<std::string> get_ref() const { return ref; }
        void set_ref(boost::optional<std::string> value) { this->ref = value; }
    };

    class PurpleData {
        public:
        PurpleData() = default;
        virtual ~PurpleData() = default;

        private:
        std::string description;

        public:
        const std::string & get_description() const { return description; }
        std::string & get_mutable_description() { return description; }
        void set_description(const std::string & value) { this->description = value; }
    };

    class ErrorProperties {
        public:
        ErrorProperties() = default;
        virtual ~ErrorProperties() = default;

        private:
        Cursor code;
        PurpleData data;
        Cursor message;

        public:
        const Cursor & get_code() const { return code; }
        Cursor & get_mutable_code() { return code; }
        void set_code(const Cursor & value) { this->code = value; }

        const PurpleData & get_data() const { return data; }
        PurpleData & get_mutable_data() { return data; }
        void set_data(const PurpleData & value) { this->data = value; }

        const Cursor & get_message() const { return message; }
        Cursor & get_mutable_message() { return message; }
        void set_message(const Cursor & value) { this->message = value; }
    };

    class Error {
        public:
        Error() = default;
        virtual ~Error() = default;

        private:
        ErrorProperties properties;
        std::vector<std::string> required;
        AnnotationsType type;

        public:
        const ErrorProperties & get_properties() const { return properties; }
        ErrorProperties & get_mutable_properties() { return properties; }
        void set_properties(const ErrorProperties & value) { this->properties = value; }

        const std::vector<std::string> & get_required() const { return required; }
        std::vector<std::string> & get_mutable_required() { return required; }
        void set_required(const std::vector<std::string> & value) { this->required = value; }

        const AnnotationsType & get_type() const { return type; }
        AnnotationsType & get_mutable_type() { return type; }
        void set_type(const AnnotationsType & value) { this->type = value; }
    };

    class JsonrpcErrorProperties {
        public:
        JsonrpcErrorProperties() = default;
        virtual ~JsonrpcErrorProperties() = default;

        private:
        Error error;
        EmptyResult id;
        TypeClass jsonrpc;

        public:
        const Error & get_error() const { return error; }
        Error & get_mutable_error() { return error; }
        void set_error(const Error & value) { this->error = value; }

        const EmptyResult & get_id() const { return id; }
        EmptyResult & get_mutable_id() { return id; }
        void set_id(const EmptyResult & value) { this->id = value; }

        const TypeClass & get_jsonrpc() const { return jsonrpc; }
        TypeClass & get_mutable_jsonrpc() { return jsonrpc; }
        void set_jsonrpc(const TypeClass & value) { this->jsonrpc = value; }
    };

    class JsonrpcError {
        public:
        JsonrpcError() = default;
        virtual ~JsonrpcError() = default;

        private:
        std::string description;
        JsonrpcErrorProperties properties;
        std::vector<std::string> required;
        AnnotationsType type;

        public:
        const std::string & get_description() const { return description; }
        std::string & get_mutable_description() { return description; }
        void set_description(const std::string & value) { this->description = value; }

        const JsonrpcErrorProperties & get_properties() const { return properties; }
        JsonrpcErrorProperties & get_mutable_properties() { return properties; }
        void set_properties(const JsonrpcErrorProperties & value) { this->properties = value; }

        const std::vector<std::string> & get_required() const { return required; }
        std::vector<std::string> & get_mutable_required() { return required; }
        void set_required(const std::vector<std::string> & value) { this->required = value; }

        const AnnotationsType & get_type() const { return type; }
        AnnotationsType & get_mutable_type() { return type; }
        void set_type(const AnnotationsType & value) { this->type = value; }
    };

    class JsonrpcMessage {
        public:
        JsonrpcMessage() = default;
        virtual ~JsonrpcMessage() = default;

        private:
        std::vector<JsonrpcBatchRequest> any_of;
        std::string description;

        public:
        const std::vector<JsonrpcBatchRequest> & get_any_of() const { return any_of; }
        std::vector<JsonrpcBatchRequest> & get_mutable_any_of() { return any_of; }
        void set_any_of(const std::vector<JsonrpcBatchRequest> & value) { this->any_of = value; }

        const std::string & get_description() const { return description; }
        std::string & get_mutable_description() { return description; }
        void set_description(const std::string & value) { this->description = value; }
    };

    class JsonrpcNotificationProperties {
        public:
        JsonrpcNotificationProperties() = default;
        virtual ~JsonrpcNotificationProperties() = default;

        private:
        TypeClass jsonrpc;
        Name method;
        Result params;

        public:
        const TypeClass & get_jsonrpc() const { return jsonrpc; }
        TypeClass & get_mutable_jsonrpc() { return jsonrpc; }
        void set_jsonrpc(const TypeClass & value) { this->jsonrpc = value; }

        const Name & get_method() const { return method; }
        Name & get_mutable_method() { return method; }
        void set_method(const Name & value) { this->method = value; }

        const Result & get_params() const { return params; }
        Result & get_mutable_params() { return params; }
        void set_params(const Result & value) { this->params = value; }
    };

    class JsonrpcNotification {
        public:
        JsonrpcNotification() = default;
        virtual ~JsonrpcNotification() = default;

        private:
        std::string description;
        JsonrpcNotificationProperties properties;
        std::vector<std::string> required;
        AnnotationsType type;

        public:
        const std::string & get_description() const { return description; }
        std::string & get_mutable_description() { return description; }
        void set_description(const std::string & value) { this->description = value; }

        const JsonrpcNotificationProperties & get_properties() const { return properties; }
        JsonrpcNotificationProperties & get_mutable_properties() { return properties; }
        void set_properties(const JsonrpcNotificationProperties & value) { this->properties = value; }

        const std::vector<std::string> & get_required() const { return required; }
        std::vector<std::string> & get_mutable_required() { return required; }
        void set_required(const std::vector<std::string> & value) { this->required = value; }

        const AnnotationsType & get_type() const { return type; }
        AnnotationsType & get_mutable_type() { return type; }
        void set_type(const AnnotationsType & value) { this->type = value; }
    };

    class CunningProperties {
        public:
        CunningProperties() = default;
        virtual ~CunningProperties() = default;

        private:
        AnnotationsClass progress_token;

        public:
        const AnnotationsClass & get_progress_token() const { return progress_token; }
        AnnotationsClass & get_mutable_progress_token() { return progress_token; }
        void set_progress_token(const AnnotationsClass & value) { this->progress_token = value; }
    };

    class FluffyMeta {
        public:
        FluffyMeta() = default;
        virtual ~FluffyMeta() = default;

        private:
        CunningProperties properties;
        AnnotationsType type;

        public:
        const CunningProperties & get_properties() const { return properties; }
        CunningProperties & get_mutable_properties() { return properties; }
        void set_properties(const CunningProperties & value) { this->properties = value; }

        const AnnotationsType & get_type() const { return type; }
        AnnotationsType & get_mutable_type() { return type; }
        void set_type(const AnnotationsType & value) { this->type = value; }
    };

    class AmbitiousProperties {
        public:
        AmbitiousProperties() = default;
        virtual ~AmbitiousProperties() = default;

        private:
        FluffyMeta meta;

        public:
        const FluffyMeta & get_meta() const { return meta; }
        FluffyMeta & get_mutable_meta() { return meta; }
        void set_meta(const FluffyMeta & value) { this->meta = value; }
    };

    class HilariousParams {
        public:
        HilariousParams() = default;
        virtual ~HilariousParams() = default;

        private:
        AdditionalPropertiesClass additional_properties;
        AmbitiousProperties properties;
        AnnotationsType type;

        public:
        const AdditionalPropertiesClass & get_additional_properties() const { return additional_properties; }
        AdditionalPropertiesClass & get_mutable_additional_properties() { return additional_properties; }
        void set_additional_properties(const AdditionalPropertiesClass & value) { this->additional_properties = value; }

        const AmbitiousProperties & get_properties() const { return properties; }
        AmbitiousProperties & get_mutable_properties() { return properties; }
        void set_properties(const AmbitiousProperties & value) { this->properties = value; }

        const AnnotationsType & get_type() const { return type; }
        AnnotationsType & get_mutable_type() { return type; }
        void set_type(const AnnotationsType & value) { this->type = value; }
    };

    class JsonrpcRequestProperties {
        public:
        JsonrpcRequestProperties() = default;
        virtual ~JsonrpcRequestProperties() = default;

        private:
        EmptyResult id;
        TypeClass jsonrpc;
        Name method;
        HilariousParams params;

        public:
        const EmptyResult & get_id() const { return id; }
        EmptyResult & get_mutable_id() { return id; }
        void set_id(const EmptyResult & value) { this->id = value; }

        const TypeClass & get_jsonrpc() const { return jsonrpc; }
        TypeClass & get_mutable_jsonrpc() { return jsonrpc; }
        void set_jsonrpc(const TypeClass & value) { this->jsonrpc = value; }

        const Name & get_method() const { return method; }
        Name & get_mutable_method() { return method; }
        void set_method(const Name & value) { this->method = value; }

        const HilariousParams & get_params() const { return params; }
        HilariousParams & get_mutable_params() { return params; }
        void set_params(const HilariousParams & value) { this->params = value; }
    };

    class JsonrpcRequest {
        public:
        JsonrpcRequest() = default;
        virtual ~JsonrpcRequest() = default;

        private:
        std::string description;
        JsonrpcRequestProperties properties;
        std::vector<std::string> required;
        AnnotationsType type;

        public:
        const std::string & get_description() const { return description; }
        std::string & get_mutable_description() { return description; }
        void set_description(const std::string & value) { this->description = value; }

        const JsonrpcRequestProperties & get_properties() const { return properties; }
        JsonrpcRequestProperties & get_mutable_properties() { return properties; }
        void set_properties(const JsonrpcRequestProperties & value) { this->properties = value; }

        const std::vector<std::string> & get_required() const { return required; }
        std::vector<std::string> & get_mutable_required() { return required; }
        void set_required(const std::vector<std::string> & value) { this->required = value; }

        const AnnotationsType & get_type() const { return type; }
        AnnotationsType & get_mutable_type() { return type; }
        void set_type(const AnnotationsType & value) { this->type = value; }
    };

    class JsonrpcResponseProperties {
        public:
        JsonrpcResponseProperties() = default;
        virtual ~JsonrpcResponseProperties() = default;

        private:
        EmptyResult id;
        TypeClass jsonrpc;
        EmptyResult result;

        public:
        const EmptyResult & get_id() const { return id; }
        EmptyResult & get_mutable_id() { return id; }
        void set_id(const EmptyResult & value) { this->id = value; }

        const TypeClass & get_jsonrpc() const { return jsonrpc; }
        TypeClass & get_mutable_jsonrpc() { return jsonrpc; }
        void set_jsonrpc(const TypeClass & value) { this->jsonrpc = value; }

        const EmptyResult & get_result() const { return result; }
        EmptyResult & get_mutable_result() { return result; }
        void set_result(const EmptyResult & value) { this->result = value; }
    };

    class JsonrpcResponse {
        public:
        JsonrpcResponse() = default;
        virtual ~JsonrpcResponse() = default;

        private:
        std::string description;
        JsonrpcResponseProperties properties;
        std::vector<std::string> required;
        AnnotationsType type;

        public:
        const std::string & get_description() const { return description; }
        std::string & get_mutable_description() { return description; }
        void set_description(const std::string & value) { this->description = value; }

        const JsonrpcResponseProperties & get_properties() const { return properties; }
        JsonrpcResponseProperties & get_mutable_properties() { return properties; }
        void set_properties(const JsonrpcResponseProperties & value) { this->properties = value; }

        const std::vector<std::string> & get_required() const { return required; }
        std::vector<std::string> & get_mutable_required() { return required; }
        void set_required(const std::vector<std::string> & value) { this->required = value; }

        const AnnotationsType & get_type() const { return type; }
        AnnotationsType & get_mutable_type() { return type; }
        void set_type(const AnnotationsType & value) { this->type = value; }
    };

    class MagentaProperties {
        public:
        MagentaProperties() = default;
        virtual ~MagentaProperties() = default;

        private:
        Cursor cursor;

        public:
        const Cursor & get_cursor() const { return cursor; }
        Cursor & get_mutable_cursor() { return cursor; }
        void set_cursor(const Cursor & value) { this->cursor = value; }
    };

    class AmbitiousParams {
        public:
        AmbitiousParams() = default;
        virtual ~AmbitiousParams() = default;

        private:
        MagentaProperties properties;
        AnnotationsType type;

        public:
        const MagentaProperties & get_properties() const { return properties; }
        MagentaProperties & get_mutable_properties() { return properties; }
        void set_properties(const MagentaProperties & value) { this->properties = value; }

        const AnnotationsType & get_type() const { return type; }
        AnnotationsType & get_mutable_type() { return type; }
        void set_type(const AnnotationsType & value) { this->type = value; }
    };

    class ListPromptsRequestProperties {
        public:
        ListPromptsRequestProperties() = default;
        virtual ~ListPromptsRequestProperties() = default;

        private:
        TypeClass method;
        AmbitiousParams params;

        public:
        const TypeClass & get_method() const { return method; }
        TypeClass & get_mutable_method() { return method; }
        void set_method(const TypeClass & value) { this->method = value; }

        const AmbitiousParams & get_params() const { return params; }
        AmbitiousParams & get_mutable_params() { return params; }
        void set_params(const AmbitiousParams & value) { this->params = value; }
    };

    class ListSRequest {
        public:
        ListSRequest() = default;
        virtual ~ListSRequest() = default;

        private:
        std::string description;
        ListPromptsRequestProperties properties;
        std::vector<std::string> required;
        AnnotationsType type;

        public:
        const std::string & get_description() const { return description; }
        std::string & get_mutable_description() { return description; }
        void set_description(const std::string & value) { this->description = value; }

        const ListPromptsRequestProperties & get_properties() const { return properties; }
        ListPromptsRequestProperties & get_mutable_properties() { return properties; }
        void set_properties(const ListPromptsRequestProperties & value) { this->properties = value; }

        const std::vector<std::string> & get_required() const { return required; }
        std::vector<std::string> & get_mutable_required() { return required; }
        void set_required(const std::vector<std::string> & value) { this->required = value; }

        const AnnotationsType & get_type() const { return type; }
        AnnotationsType & get_mutable_type() { return type; }
        void set_type(const AnnotationsType & value) { this->type = value; }
    };

    class ListPromptsResultProperties {
        public:
        ListPromptsResultProperties() = default;
        virtual ~ListPromptsResultProperties() = default;

        private:
        PurpleMeta meta;
        Cursor next_cursor;
        Messages prompts;

        public:
        const PurpleMeta & get_meta() const { return meta; }
        PurpleMeta & get_mutable_meta() { return meta; }
        void set_meta(const PurpleMeta & value) { this->meta = value; }

        const Cursor & get_next_cursor() const { return next_cursor; }
        Cursor & get_mutable_next_cursor() { return next_cursor; }
        void set_next_cursor(const Cursor & value) { this->next_cursor = value; }

        const Messages & get_prompts() const { return prompts; }
        Messages & get_mutable_prompts() { return prompts; }
        void set_prompts(const Messages & value) { this->prompts = value; }
    };

    class ListPromptsResult {
        public:
        ListPromptsResult() = default;
        virtual ~ListPromptsResult() = default;

        private:
        std::string description;
        ListPromptsResultProperties properties;
        std::vector<std::string> required;
        AnnotationsType type;

        public:
        const std::string & get_description() const { return description; }
        std::string & get_mutable_description() { return description; }
        void set_description(const std::string & value) { this->description = value; }

        const ListPromptsResultProperties & get_properties() const { return properties; }
        ListPromptsResultProperties & get_mutable_properties() { return properties; }
        void set_properties(const ListPromptsResultProperties & value) { this->properties = value; }

        const std::vector<std::string> & get_required() const { return required; }
        std::vector<std::string> & get_mutable_required() { return required; }
        void set_required(const std::vector<std::string> & value) { this->required = value; }

        const AnnotationsType & get_type() const { return type; }
        AnnotationsType & get_mutable_type() { return type; }
        void set_type(const AnnotationsType & value) { this->type = value; }
    };

    class ListResourceTemplatesResultProperties {
        public:
        ListResourceTemplatesResultProperties() = default;
        virtual ~ListResourceTemplatesResultProperties() = default;

        private:
        PurpleMeta meta;
        Cursor next_cursor;
        Messages resource_templates;

        public:
        const PurpleMeta & get_meta() const { return meta; }
        PurpleMeta & get_mutable_meta() { return meta; }
        void set_meta(const PurpleMeta & value) { this->meta = value; }

        const Cursor & get_next_cursor() const { return next_cursor; }
        Cursor & get_mutable_next_cursor() { return next_cursor; }
        void set_next_cursor(const Cursor & value) { this->next_cursor = value; }

        const Messages & get_resource_templates() const { return resource_templates; }
        Messages & get_mutable_resource_templates() { return resource_templates; }
        void set_resource_templates(const Messages & value) { this->resource_templates = value; }
    };

    class ListResourceTemplatesResult {
        public:
        ListResourceTemplatesResult() = default;
        virtual ~ListResourceTemplatesResult() = default;

        private:
        std::string description;
        ListResourceTemplatesResultProperties properties;
        std::vector<std::string> required;
        AnnotationsType type;

        public:
        const std::string & get_description() const { return description; }
        std::string & get_mutable_description() { return description; }
        void set_description(const std::string & value) { this->description = value; }

        const ListResourceTemplatesResultProperties & get_properties() const { return properties; }
        ListResourceTemplatesResultProperties & get_mutable_properties() { return properties; }
        void set_properties(const ListResourceTemplatesResultProperties & value) { this->properties = value; }

        const std::vector<std::string> & get_required() const { return required; }
        std::vector<std::string> & get_mutable_required() { return required; }
        void set_required(const std::vector<std::string> & value) { this->required = value; }

        const AnnotationsType & get_type() const { return type; }
        AnnotationsType & get_mutable_type() { return type; }
        void set_type(const AnnotationsType & value) { this->type = value; }
    };

    class ListResourcesResultProperties {
        public:
        ListResourcesResultProperties() = default;
        virtual ~ListResourcesResultProperties() = default;

        private:
        PurpleMeta meta;
        Cursor next_cursor;
        Messages resources;

        public:
        const PurpleMeta & get_meta() const { return meta; }
        PurpleMeta & get_mutable_meta() { return meta; }
        void set_meta(const PurpleMeta & value) { this->meta = value; }

        const Cursor & get_next_cursor() const { return next_cursor; }
        Cursor & get_mutable_next_cursor() { return next_cursor; }
        void set_next_cursor(const Cursor & value) { this->next_cursor = value; }

        const Messages & get_resources() const { return resources; }
        Messages & get_mutable_resources() { return resources; }
        void set_resources(const Messages & value) { this->resources = value; }
    };

    class ListResourcesResult {
        public:
        ListResourcesResult() = default;
        virtual ~ListResourcesResult() = default;

        private:
        std::string description;
        ListResourcesResultProperties properties;
        std::vector<std::string> required;
        AnnotationsType type;

        public:
        const std::string & get_description() const { return description; }
        std::string & get_mutable_description() { return description; }
        void set_description(const std::string & value) { this->description = value; }

        const ListResourcesResultProperties & get_properties() const { return properties; }
        ListResourcesResultProperties & get_mutable_properties() { return properties; }
        void set_properties(const ListResourcesResultProperties & value) { this->properties = value; }

        const std::vector<std::string> & get_required() const { return required; }
        std::vector<std::string> & get_mutable_required() { return required; }
        void set_required(const std::vector<std::string> & value) { this->required = value; }

        const AnnotationsType & get_type() const { return type; }
        AnnotationsType & get_mutable_type() { return type; }
        void set_type(const AnnotationsType & value) { this->type = value; }
    };

    class ListRootsRequestProperties {
        public:
        ListRootsRequestProperties() = default;
        virtual ~ListRootsRequestProperties() = default;

        private:
        TypeClass method;
        HilariousParams params;

        public:
        const TypeClass & get_method() const { return method; }
        TypeClass & get_mutable_method() { return method; }
        void set_method(const TypeClass & value) { this->method = value; }

        const HilariousParams & get_params() const { return params; }
        HilariousParams & get_mutable_params() { return params; }
        void set_params(const HilariousParams & value) { this->params = value; }
    };

    class Request {
        public:
        Request() = default;
        virtual ~Request() = default;

        private:
        std::string description;
        ListRootsRequestProperties properties;
        std::vector<std::string> required;
        AnnotationsType type;

        public:
        const std::string & get_description() const { return description; }
        std::string & get_mutable_description() { return description; }
        void set_description(const std::string & value) { this->description = value; }

        const ListRootsRequestProperties & get_properties() const { return properties; }
        ListRootsRequestProperties & get_mutable_properties() { return properties; }
        void set_properties(const ListRootsRequestProperties & value) { this->properties = value; }

        const std::vector<std::string> & get_required() const { return required; }
        std::vector<std::string> & get_mutable_required() { return required; }
        void set_required(const std::vector<std::string> & value) { this->required = value; }

        const AnnotationsType & get_type() const { return type; }
        AnnotationsType & get_mutable_type() { return type; }
        void set_type(const AnnotationsType & value) { this->type = value; }
    };

    class ListRootsResultProperties {
        public:
        ListRootsResultProperties() = default;
        virtual ~ListRootsResultProperties() = default;

        private:
        PurpleMeta meta;
        Messages roots;

        public:
        const PurpleMeta & get_meta() const { return meta; }
        PurpleMeta & get_mutable_meta() { return meta; }
        void set_meta(const PurpleMeta & value) { this->meta = value; }

        const Messages & get_roots() const { return roots; }
        Messages & get_mutable_roots() { return roots; }
        void set_roots(const Messages & value) { this->roots = value; }
    };

    class ListRootsResult {
        public:
        ListRootsResult() = default;
        virtual ~ListRootsResult() = default;

        private:
        std::string description;
        ListRootsResultProperties properties;
        std::vector<std::string> required;
        AnnotationsType type;

        public:
        const std::string & get_description() const { return description; }
        std::string & get_mutable_description() { return description; }
        void set_description(const std::string & value) { this->description = value; }

        const ListRootsResultProperties & get_properties() const { return properties; }
        ListRootsResultProperties & get_mutable_properties() { return properties; }
        void set_properties(const ListRootsResultProperties & value) { this->properties = value; }

        const std::vector<std::string> & get_required() const { return required; }
        std::vector<std::string> & get_mutable_required() { return required; }
        void set_required(const std::vector<std::string> & value) { this->required = value; }

        const AnnotationsType & get_type() const { return type; }
        AnnotationsType & get_mutable_type() { return type; }
        void set_type(const AnnotationsType & value) { this->type = value; }
    };

    class ListToolsResultProperties {
        public:
        ListToolsResultProperties() = default;
        virtual ~ListToolsResultProperties() = default;

        private:
        PurpleMeta meta;
        Cursor next_cursor;
        Messages tools;

        public:
        const PurpleMeta & get_meta() const { return meta; }
        PurpleMeta & get_mutable_meta() { return meta; }
        void set_meta(const PurpleMeta & value) { this->meta = value; }

        const Cursor & get_next_cursor() const { return next_cursor; }
        Cursor & get_mutable_next_cursor() { return next_cursor; }
        void set_next_cursor(const Cursor & value) { this->next_cursor = value; }

        const Messages & get_tools() const { return tools; }
        Messages & get_mutable_tools() { return tools; }
        void set_tools(const Messages & value) { this->tools = value; }
    };

    class ListToolsResult {
        public:
        ListToolsResult() = default;
        virtual ~ListToolsResult() = default;

        private:
        std::string description;
        ListToolsResultProperties properties;
        std::vector<std::string> required;
        AnnotationsType type;

        public:
        const std::string & get_description() const { return description; }
        std::string & get_mutable_description() { return description; }
        void set_description(const std::string & value) { this->description = value; }

        const ListToolsResultProperties & get_properties() const { return properties; }
        ListToolsResultProperties & get_mutable_properties() { return properties; }
        void set_properties(const ListToolsResultProperties & value) { this->properties = value; }

        const std::vector<std::string> & get_required() const { return required; }
        std::vector<std::string> & get_mutable_required() { return required; }
        void set_required(const std::vector<std::string> & value) { this->required = value; }

        const AnnotationsType & get_type() const { return type; }
        AnnotationsType & get_mutable_type() { return type; }
        void set_type(const AnnotationsType & value) { this->type = value; }
    };

    class FriskyProperties {
        public:
        FriskyProperties() = default;
        virtual ~FriskyProperties() = default;

        private:
        PurpleData data;
        AnnotationsClass level;
        Cursor logger;

        public:
        const PurpleData & get_data() const { return data; }
        PurpleData & get_mutable_data() { return data; }
        void set_data(const PurpleData & value) { this->data = value; }

        const AnnotationsClass & get_level() const { return level; }
        AnnotationsClass & get_mutable_level() { return level; }
        void set_level(const AnnotationsClass & value) { this->level = value; }

        const Cursor & get_logger() const { return logger; }
        Cursor & get_mutable_logger() { return logger; }
        void set_logger(const Cursor & value) { this->logger = value; }
    };

    class CunningParams {
        public:
        CunningParams() = default;
        virtual ~CunningParams() = default;

        private:
        FriskyProperties properties;
        std::vector<std::string> required;
        AnnotationsType type;

        public:
        const FriskyProperties & get_properties() const { return properties; }
        FriskyProperties & get_mutable_properties() { return properties; }
        void set_properties(const FriskyProperties & value) { this->properties = value; }

        const std::vector<std::string> & get_required() const { return required; }
        std::vector<std::string> & get_mutable_required() { return required; }
        void set_required(const std::vector<std::string> & value) { this->required = value; }

        const AnnotationsType & get_type() const { return type; }
        AnnotationsType & get_mutable_type() { return type; }
        void set_type(const AnnotationsType & value) { this->type = value; }
    };

    class LoggingMessageNotificationProperties {
        public:
        LoggingMessageNotificationProperties() = default;
        virtual ~LoggingMessageNotificationProperties() = default;

        private:
        TypeClass method;
        CunningParams params;

        public:
        const TypeClass & get_method() const { return method; }
        TypeClass & get_mutable_method() { return method; }
        void set_method(const TypeClass & value) { this->method = value; }

        const CunningParams & get_params() const { return params; }
        CunningParams & get_mutable_params() { return params; }
        void set_params(const CunningParams & value) { this->params = value; }
    };

    class LoggingMessageNotification {
        public:
        LoggingMessageNotification() = default;
        virtual ~LoggingMessageNotification() = default;

        private:
        std::string description;
        LoggingMessageNotificationProperties properties;
        std::vector<std::string> required;
        AnnotationsType type;

        public:
        const std::string & get_description() const { return description; }
        std::string & get_mutable_description() { return description; }
        void set_description(const std::string & value) { this->description = value; }

        const LoggingMessageNotificationProperties & get_properties() const { return properties; }
        LoggingMessageNotificationProperties & get_mutable_properties() { return properties; }
        void set_properties(const LoggingMessageNotificationProperties & value) { this->properties = value; }

        const std::vector<std::string> & get_required() const { return required; }
        std::vector<std::string> & get_mutable_required() { return required; }
        void set_required(const std::vector<std::string> & value) { this->required = value; }

        const AnnotationsType & get_type() const { return type; }
        AnnotationsType & get_mutable_type() { return type; }
        void set_type(const AnnotationsType & value) { this->type = value; }
    };

    class ModelHintProperties {
        public:
        ModelHintProperties() = default;
        virtual ~ModelHintProperties() = default;

        private:
        Cursor name;

        public:
        const Cursor & get_name() const { return name; }
        Cursor & get_mutable_name() { return name; }
        void set_name(const Cursor & value) { this->name = value; }
    };

    class ModelHint {
        public:
        ModelHint() = default;
        virtual ~ModelHint() = default;

        private:
        std::string description;
        ModelHintProperties properties;
        AnnotationsType type;

        public:
        const std::string & get_description() const { return description; }
        std::string & get_mutable_description() { return description; }
        void set_description(const std::string & value) { this->description = value; }

        const ModelHintProperties & get_properties() const { return properties; }
        ModelHintProperties & get_mutable_properties() { return properties; }
        void set_properties(const ModelHintProperties & value) { this->properties = value; }

        const AnnotationsType & get_type() const { return type; }
        AnnotationsType & get_mutable_type() { return type; }
        void set_type(const AnnotationsType & value) { this->type = value; }
    };

    class ModelPreferencesProperties {
        public:
        ModelPreferencesProperties() = default;
        virtual ~ModelPreferencesProperties() = default;

        private:
        Priority cost_priority;
        Audience hints;
        Priority intelligence_priority;
        Priority speed_priority;

        public:
        const Priority & get_cost_priority() const { return cost_priority; }
        Priority & get_mutable_cost_priority() { return cost_priority; }
        void set_cost_priority(const Priority & value) { this->cost_priority = value; }

        const Audience & get_hints() const { return hints; }
        Audience & get_mutable_hints() { return hints; }
        void set_hints(const Audience & value) { this->hints = value; }

        const Priority & get_intelligence_priority() const { return intelligence_priority; }
        Priority & get_mutable_intelligence_priority() { return intelligence_priority; }
        void set_intelligence_priority(const Priority & value) { this->intelligence_priority = value; }

        const Priority & get_speed_priority() const { return speed_priority; }
        Priority & get_mutable_speed_priority() { return speed_priority; }
        void set_speed_priority(const Priority & value) { this->speed_priority = value; }
    };

    class ModelPreferences {
        public:
        ModelPreferences() = default;
        virtual ~ModelPreferences() = default;

        private:
        std::string description;
        ModelPreferencesProperties properties;
        AnnotationsType type;

        public:
        const std::string & get_description() const { return description; }
        std::string & get_mutable_description() { return description; }
        void set_description(const std::string & value) { this->description = value; }

        const ModelPreferencesProperties & get_properties() const { return properties; }
        ModelPreferencesProperties & get_mutable_properties() { return properties; }
        void set_properties(const ModelPreferencesProperties & value) { this->properties = value; }

        const AnnotationsType & get_type() const { return type; }
        AnnotationsType & get_mutable_type() { return type; }
        void set_type(const AnnotationsType & value) { this->type = value; }
    };

    class NotificationProperties {
        public:
        NotificationProperties() = default;
        virtual ~NotificationProperties() = default;

        private:
        Name method;
        Result params;

        public:
        const Name & get_method() const { return method; }
        Name & get_mutable_method() { return method; }
        void set_method(const Name & value) { this->method = value; }

        const Result & get_params() const { return params; }
        Result & get_mutable_params() { return params; }
        void set_params(const Result & value) { this->params = value; }
    };

    class Notification {
        public:
        Notification() = default;
        virtual ~Notification() = default;

        private:
        NotificationProperties properties;
        std::vector<std::string> required;
        AnnotationsType type;

        public:
        const NotificationProperties & get_properties() const { return properties; }
        NotificationProperties & get_mutable_properties() { return properties; }
        void set_properties(const NotificationProperties & value) { this->properties = value; }

        const std::vector<std::string> & get_required() const { return required; }
        std::vector<std::string> & get_mutable_required() { return required; }
        void set_required(const std::vector<std::string> & value) { this->required = value; }

        const AnnotationsType & get_type() const { return type; }
        AnnotationsType & get_mutable_type() { return type; }
        void set_type(const AnnotationsType & value) { this->type = value; }
    };

    class PaginatedRequestProperties {
        public:
        PaginatedRequestProperties() = default;
        virtual ~PaginatedRequestProperties() = default;

        private:
        Name method;
        AmbitiousParams params;

        public:
        const Name & get_method() const { return method; }
        Name & get_mutable_method() { return method; }
        void set_method(const Name & value) { this->method = value; }

        const AmbitiousParams & get_params() const { return params; }
        AmbitiousParams & get_mutable_params() { return params; }
        void set_params(const AmbitiousParams & value) { this->params = value; }
    };

    class PaginatedRequest {
        public:
        PaginatedRequest() = default;
        virtual ~PaginatedRequest() = default;

        private:
        PaginatedRequestProperties properties;
        std::vector<std::string> required;
        AnnotationsType type;

        public:
        const PaginatedRequestProperties & get_properties() const { return properties; }
        PaginatedRequestProperties & get_mutable_properties() { return properties; }
        void set_properties(const PaginatedRequestProperties & value) { this->properties = value; }

        const std::vector<std::string> & get_required() const { return required; }
        std::vector<std::string> & get_mutable_required() { return required; }
        void set_required(const std::vector<std::string> & value) { this->required = value; }

        const AnnotationsType & get_type() const { return type; }
        AnnotationsType & get_mutable_type() { return type; }
        void set_type(const AnnotationsType & value) { this->type = value; }
    };

    class PaginatedResultProperties {
        public:
        PaginatedResultProperties() = default;
        virtual ~PaginatedResultProperties() = default;

        private:
        PurpleMeta meta;
        Cursor next_cursor;

        public:
        const PurpleMeta & get_meta() const { return meta; }
        PurpleMeta & get_mutable_meta() { return meta; }
        void set_meta(const PurpleMeta & value) { this->meta = value; }

        const Cursor & get_next_cursor() const { return next_cursor; }
        Cursor & get_mutable_next_cursor() { return next_cursor; }
        void set_next_cursor(const Cursor & value) { this->next_cursor = value; }
    };

    class PaginatedResult {
        public:
        PaginatedResult() = default;
        virtual ~PaginatedResult() = default;

        private:
        PaginatedResultProperties properties;
        AnnotationsType type;

        public:
        const PaginatedResultProperties & get_properties() const { return properties; }
        PaginatedResultProperties & get_mutable_properties() { return properties; }
        void set_properties(const PaginatedResultProperties & value) { this->properties = value; }

        const AnnotationsType & get_type() const { return type; }
        AnnotationsType & get_mutable_type() { return type; }
        void set_type(const AnnotationsType & value) { this->type = value; }
    };

    class MischievousProperties {
        public:
        MischievousProperties() = default;
        virtual ~MischievousProperties() = default;

        private:
        Cursor message;
        Cursor progress;
        AnnotationsClass progress_token;
        Cursor total;

        public:
        const Cursor & get_message() const { return message; }
        Cursor & get_mutable_message() { return message; }
        void set_message(const Cursor & value) { this->message = value; }

        const Cursor & get_progress() const { return progress; }
        Cursor & get_mutable_progress() { return progress; }
        void set_progress(const Cursor & value) { this->progress = value; }

        const AnnotationsClass & get_progress_token() const { return progress_token; }
        AnnotationsClass & get_mutable_progress_token() { return progress_token; }
        void set_progress_token(const AnnotationsClass & value) { this->progress_token = value; }

        const Cursor & get_total() const { return total; }
        Cursor & get_mutable_total() { return total; }
        void set_total(const Cursor & value) { this->total = value; }
    };

    class MagentaParams {
        public:
        MagentaParams() = default;
        virtual ~MagentaParams() = default;

        private:
        MischievousProperties properties;
        std::vector<std::string> required;
        AnnotationsType type;

        public:
        const MischievousProperties & get_properties() const { return properties; }
        MischievousProperties & get_mutable_properties() { return properties; }
        void set_properties(const MischievousProperties & value) { this->properties = value; }

        const std::vector<std::string> & get_required() const { return required; }
        std::vector<std::string> & get_mutable_required() { return required; }
        void set_required(const std::vector<std::string> & value) { this->required = value; }

        const AnnotationsType & get_type() const { return type; }
        AnnotationsType & get_mutable_type() { return type; }
        void set_type(const AnnotationsType & value) { this->type = value; }
    };

    class ProgressNotificationProperties {
        public:
        ProgressNotificationProperties() = default;
        virtual ~ProgressNotificationProperties() = default;

        private:
        TypeClass method;
        MagentaParams params;

        public:
        const TypeClass & get_method() const { return method; }
        TypeClass & get_mutable_method() { return method; }
        void set_method(const TypeClass & value) { this->method = value; }

        const MagentaParams & get_params() const { return params; }
        MagentaParams & get_mutable_params() { return params; }
        void set_params(const MagentaParams & value) { this->params = value; }
    };

    class ProgressNotification {
        public:
        ProgressNotification() = default;
        virtual ~ProgressNotification() = default;

        private:
        std::string description;
        ProgressNotificationProperties properties;
        std::vector<std::string> required;
        AnnotationsType type;

        public:
        const std::string & get_description() const { return description; }
        std::string & get_mutable_description() { return description; }
        void set_description(const std::string & value) { this->description = value; }

        const ProgressNotificationProperties & get_properties() const { return properties; }
        ProgressNotificationProperties & get_mutable_properties() { return properties; }
        void set_properties(const ProgressNotificationProperties & value) { this->properties = value; }

        const std::vector<std::string> & get_required() const { return required; }
        std::vector<std::string> & get_mutable_required() { return required; }
        void set_required(const std::vector<std::string> & value) { this->required = value; }

        const AnnotationsType & get_type() const { return type; }
        AnnotationsType & get_mutable_type() { return type; }
        void set_type(const AnnotationsType & value) { this->type = value; }
    };

    class ProgressToken {
        public:
        ProgressToken() = default;
        virtual ~ProgressToken() = default;

        private:
        std::string description;
        std::vector<TypeElement> type;

        public:
        const std::string & get_description() const { return description; }
        std::string & get_mutable_description() { return description; }
        void set_description(const std::string & value) { this->description = value; }

        const std::vector<TypeElement> & get_type() const { return type; }
        std::vector<TypeElement> & get_mutable_type() { return type; }
        void set_type(const std::vector<TypeElement> & value) { this->type = value; }
    };

    class PromptProperties {
        public:
        PromptProperties() = default;
        virtual ~PromptProperties() = default;

        private:
        Audience arguments;
        Cursor description;
        Cursor name;

        public:
        const Audience & get_arguments() const { return arguments; }
        Audience & get_mutable_arguments() { return arguments; }
        void set_arguments(const Audience & value) { this->arguments = value; }

        const Cursor & get_description() const { return description; }
        Cursor & get_mutable_description() { return description; }
        void set_description(const Cursor & value) { this->description = value; }

        const Cursor & get_name() const { return name; }
        Cursor & get_mutable_name() { return name; }
        void set_name(const Cursor & value) { this->name = value; }
    };

    class Prompt {
        public:
        Prompt() = default;
        virtual ~Prompt() = default;

        private:
        std::string description;
        PromptProperties properties;
        std::vector<std::string> required;
        AnnotationsType type;

        public:
        const std::string & get_description() const { return description; }
        std::string & get_mutable_description() { return description; }
        void set_description(const std::string & value) { this->description = value; }

        const PromptProperties & get_properties() const { return properties; }
        PromptProperties & get_mutable_properties() { return properties; }
        void set_properties(const PromptProperties & value) { this->properties = value; }

        const std::vector<std::string> & get_required() const { return required; }
        std::vector<std::string> & get_mutable_required() { return required; }
        void set_required(const std::vector<std::string> & value) { this->required = value; }

        const AnnotationsType & get_type() const { return type; }
        AnnotationsType & get_mutable_type() { return type; }
        void set_type(const AnnotationsType & value) { this->type = value; }
    };

    class PromptArgumentProperties {
        public:
        PromptArgumentProperties() = default;
        virtual ~PromptArgumentProperties() = default;

        private:
        Cursor description;
        Cursor name;
        Cursor required;

        public:
        const Cursor & get_description() const { return description; }
        Cursor & get_mutable_description() { return description; }
        void set_description(const Cursor & value) { this->description = value; }

        const Cursor & get_name() const { return name; }
        Cursor & get_mutable_name() { return name; }
        void set_name(const Cursor & value) { this->name = value; }

        const Cursor & get_required() const { return required; }
        Cursor & get_mutable_required() { return required; }
        void set_required(const Cursor & value) { this->required = value; }
    };

    class PromptArgument {
        public:
        PromptArgument() = default;
        virtual ~PromptArgument() = default;

        private:
        std::string description;
        PromptArgumentProperties properties;
        std::vector<std::string> required;
        AnnotationsType type;

        public:
        const std::string & get_description() const { return description; }
        std::string & get_mutable_description() { return description; }
        void set_description(const std::string & value) { this->description = value; }

        const PromptArgumentProperties & get_properties() const { return properties; }
        PromptArgumentProperties & get_mutable_properties() { return properties; }
        void set_properties(const PromptArgumentProperties & value) { this->properties = value; }

        const std::vector<std::string> & get_required() const { return required; }
        std::vector<std::string> & get_mutable_required() { return required; }
        void set_required(const std::vector<std::string> & value) { this->required = value; }

        const AnnotationsType & get_type() const { return type; }
        AnnotationsType & get_mutable_type() { return type; }
        void set_type(const AnnotationsType & value) { this->type = value; }
    };

    class PromptMessageProperties {
        public:
        PromptMessageProperties() = default;
        virtual ~PromptMessageProperties() = default;

        private:
        ClientNotification content;
        EmptyResult role;

        public:
        const ClientNotification & get_content() const { return content; }
        ClientNotification & get_mutable_content() { return content; }
        void set_content(const ClientNotification & value) { this->content = value; }

        const EmptyResult & get_role() const { return role; }
        EmptyResult & get_mutable_role() { return role; }
        void set_role(const EmptyResult & value) { this->role = value; }
    };

    class Message {
        public:
        Message() = default;
        virtual ~Message() = default;

        private:
        std::string description;
        PromptMessageProperties properties;
        std::vector<std::string> required;
        AnnotationsType type;

        public:
        const std::string & get_description() const { return description; }
        std::string & get_mutable_description() { return description; }
        void set_description(const std::string & value) { this->description = value; }

        const PromptMessageProperties & get_properties() const { return properties; }
        PromptMessageProperties & get_mutable_properties() { return properties; }
        void set_properties(const PromptMessageProperties & value) { this->properties = value; }

        const std::vector<std::string> & get_required() const { return required; }
        std::vector<std::string> & get_mutable_required() { return required; }
        void set_required(const std::vector<std::string> & value) { this->required = value; }

        const AnnotationsType & get_type() const { return type; }
        AnnotationsType & get_mutable_type() { return type; }
        void set_type(const AnnotationsType & value) { this->type = value; }
    };

    class PromptReferenceProperties {
        public:
        PromptReferenceProperties() = default;
        virtual ~PromptReferenceProperties() = default;

        private:
        Cursor name;
        TypeClass type;

        public:
        const Cursor & get_name() const { return name; }
        Cursor & get_mutable_name() { return name; }
        void set_name(const Cursor & value) { this->name = value; }

        const TypeClass & get_type() const { return type; }
        TypeClass & get_mutable_type() { return type; }
        void set_type(const TypeClass & value) { this->type = value; }
    };

    class PromptReference {
        public:
        PromptReference() = default;
        virtual ~PromptReference() = default;

        private:
        std::string description;
        PromptReferenceProperties properties;
        std::vector<std::string> required;
        AnnotationsType type;

        public:
        const std::string & get_description() const { return description; }
        std::string & get_mutable_description() { return description; }
        void set_description(const std::string & value) { this->description = value; }

        const PromptReferenceProperties & get_properties() const { return properties; }
        PromptReferenceProperties & get_mutable_properties() { return properties; }
        void set_properties(const PromptReferenceProperties & value) { this->properties = value; }

        const std::vector<std::string> & get_required() const { return required; }
        std::vector<std::string> & get_mutable_required() { return required; }
        void set_required(const std::vector<std::string> & value) { this->required = value; }

        const AnnotationsType & get_type() const { return type; }
        AnnotationsType & get_mutable_type() { return type; }
        void set_type(const AnnotationsType & value) { this->type = value; }
    };

    class BraggadociousProperties {
        public:
        BraggadociousProperties() = default;
        virtual ~BraggadociousProperties() = default;

        private:
        BlobClass uri;

        public:
        const BlobClass & get_uri() const { return uri; }
        BlobClass & get_mutable_uri() { return uri; }
        void set_uri(const BlobClass & value) { this->uri = value; }
    };

    class FriskyParams {
        public:
        FriskyParams() = default;
        virtual ~FriskyParams() = default;

        private:
        BraggadociousProperties properties;
        std::vector<Required> required;
        AnnotationsType type;

        public:
        const BraggadociousProperties & get_properties() const { return properties; }
        BraggadociousProperties & get_mutable_properties() { return properties; }
        void set_properties(const BraggadociousProperties & value) { this->properties = value; }

        const std::vector<Required> & get_required() const { return required; }
        std::vector<Required> & get_mutable_required() { return required; }
        void set_required(const std::vector<Required> & value) { this->required = value; }

        const AnnotationsType & get_type() const { return type; }
        AnnotationsType & get_mutable_type() { return type; }
        void set_type(const AnnotationsType & value) { this->type = value; }
    };

    class ReadResourceRequestProperties {
        public:
        ReadResourceRequestProperties() = default;
        virtual ~ReadResourceRequestProperties() = default;

        private:
        TypeClass method;
        FriskyParams params;

        public:
        const TypeClass & get_method() const { return method; }
        TypeClass & get_mutable_method() { return method; }
        void set_method(const TypeClass & value) { this->method = value; }

        const FriskyParams & get_params() const { return params; }
        FriskyParams & get_mutable_params() { return params; }
        void set_params(const FriskyParams & value) { this->params = value; }
    };

    class ReadResourceRequest {
        public:
        ReadResourceRequest() = default;
        virtual ~ReadResourceRequest() = default;

        private:
        std::string description;
        ReadResourceRequestProperties properties;
        std::vector<std::string> required;
        AnnotationsType type;

        public:
        const std::string & get_description() const { return description; }
        std::string & get_mutable_description() { return description; }
        void set_description(const std::string & value) { this->description = value; }

        const ReadResourceRequestProperties & get_properties() const { return properties; }
        ReadResourceRequestProperties & get_mutable_properties() { return properties; }
        void set_properties(const ReadResourceRequestProperties & value) { this->properties = value; }

        const std::vector<std::string> & get_required() const { return required; }
        std::vector<std::string> & get_mutable_required() { return required; }
        void set_required(const std::vector<std::string> & value) { this->required = value; }

        const AnnotationsType & get_type() const { return type; }
        AnnotationsType & get_mutable_type() { return type; }
        void set_type(const AnnotationsType & value) { this->type = value; }
    };

    class ReadResourceResultProperties {
        public:
        ReadResourceResultProperties() = default;
        virtual ~ReadResourceResultProperties() = default;

        private:
        PurpleMeta meta;
        ContentClass contents;

        public:
        const PurpleMeta & get_meta() const { return meta; }
        PurpleMeta & get_mutable_meta() { return meta; }
        void set_meta(const PurpleMeta & value) { this->meta = value; }

        const ContentClass & get_contents() const { return contents; }
        ContentClass & get_mutable_contents() { return contents; }
        void set_contents(const ContentClass & value) { this->contents = value; }
    };

    class ReadResourceResult {
        public:
        ReadResourceResult() = default;
        virtual ~ReadResourceResult() = default;

        private:
        std::string description;
        ReadResourceResultProperties properties;
        std::vector<std::string> required;
        AnnotationsType type;

        public:
        const std::string & get_description() const { return description; }
        std::string & get_mutable_description() { return description; }
        void set_description(const std::string & value) { this->description = value; }

        const ReadResourceResultProperties & get_properties() const { return properties; }
        ReadResourceResultProperties & get_mutable_properties() { return properties; }
        void set_properties(const ReadResourceResultProperties & value) { this->properties = value; }

        const std::vector<std::string> & get_required() const { return required; }
        std::vector<std::string> & get_mutable_required() { return required; }
        void set_required(const std::vector<std::string> & value) { this->required = value; }

        const AnnotationsType & get_type() const { return type; }
        AnnotationsType & get_mutable_type() { return type; }
        void set_type(const AnnotationsType & value) { this->type = value; }
    };

    class RequestProperties {
        public:
        RequestProperties() = default;
        virtual ~RequestProperties() = default;

        private:
        Name method;
        HilariousParams params;

        public:
        const Name & get_method() const { return method; }
        Name & get_mutable_method() { return method; }
        void set_method(const Name & value) { this->method = value; }

        const HilariousParams & get_params() const { return params; }
        HilariousParams & get_mutable_params() { return params; }
        void set_params(const HilariousParams & value) { this->params = value; }
    };

    class RequestClass {
        public:
        RequestClass() = default;
        virtual ~RequestClass() = default;

        private:
        RequestProperties properties;
        std::vector<std::string> required;
        AnnotationsType type;

        public:
        const RequestProperties & get_properties() const { return properties; }
        RequestProperties & get_mutable_properties() { return properties; }
        void set_properties(const RequestProperties & value) { this->properties = value; }

        const std::vector<std::string> & get_required() const { return required; }
        std::vector<std::string> & get_mutable_required() { return required; }
        void set_required(const std::vector<std::string> & value) { this->required = value; }

        const AnnotationsType & get_type() const { return type; }
        AnnotationsType & get_mutable_type() { return type; }
        void set_type(const AnnotationsType & value) { this->type = value; }
    };

    class ResourceProperties {
        public:
        ResourceProperties() = default;
        virtual ~ResourceProperties() = default;

        private:
        AnnotationsClass annotations;
        Cursor description;
        Cursor mime_type;
        Cursor name;
        Cursor size;
        BlobClass uri;

        public:
        const AnnotationsClass & get_annotations() const { return annotations; }
        AnnotationsClass & get_mutable_annotations() { return annotations; }
        void set_annotations(const AnnotationsClass & value) { this->annotations = value; }

        const Cursor & get_description() const { return description; }
        Cursor & get_mutable_description() { return description; }
        void set_description(const Cursor & value) { this->description = value; }

        const Cursor & get_mime_type() const { return mime_type; }
        Cursor & get_mutable_mime_type() { return mime_type; }
        void set_mime_type(const Cursor & value) { this->mime_type = value; }

        const Cursor & get_name() const { return name; }
        Cursor & get_mutable_name() { return name; }
        void set_name(const Cursor & value) { this->name = value; }

        const Cursor & get_size() const { return size; }
        Cursor & get_mutable_size() { return size; }
        void set_size(const Cursor & value) { this->size = value; }

        const BlobClass & get_uri() const { return uri; }
        BlobClass & get_mutable_uri() { return uri; }
        void set_uri(const BlobClass & value) { this->uri = value; }
    };

    class Resource {
        public:
        Resource() = default;
        virtual ~Resource() = default;

        private:
        std::string description;
        ResourceProperties properties;
        std::vector<std::string> required;
        AnnotationsType type;

        public:
        const std::string & get_description() const { return description; }
        std::string & get_mutable_description() { return description; }
        void set_description(const std::string & value) { this->description = value; }

        const ResourceProperties & get_properties() const { return properties; }
        ResourceProperties & get_mutable_properties() { return properties; }
        void set_properties(const ResourceProperties & value) { this->properties = value; }

        const std::vector<std::string> & get_required() const { return required; }
        std::vector<std::string> & get_mutable_required() { return required; }
        void set_required(const std::vector<std::string> & value) { this->required = value; }

        const AnnotationsType & get_type() const { return type; }
        AnnotationsType & get_mutable_type() { return type; }
        void set_type(const AnnotationsType & value) { this->type = value; }
    };

    class ResourceContentsProperties {
        public:
        ResourceContentsProperties() = default;
        virtual ~ResourceContentsProperties() = default;

        private:
        Cursor mime_type;
        BlobClass uri;

        public:
        const Cursor & get_mime_type() const { return mime_type; }
        Cursor & get_mutable_mime_type() { return mime_type; }
        void set_mime_type(const Cursor & value) { this->mime_type = value; }

        const BlobClass & get_uri() const { return uri; }
        BlobClass & get_mutable_uri() { return uri; }
        void set_uri(const BlobClass & value) { this->uri = value; }
    };

    class ResourceContents {
        public:
        ResourceContents() = default;
        virtual ~ResourceContents() = default;

        private:
        std::string description;
        ResourceContentsProperties properties;
        std::vector<Required> required;
        AnnotationsType type;

        public:
        const std::string & get_description() const { return description; }
        std::string & get_mutable_description() { return description; }
        void set_description(const std::string & value) { this->description = value; }

        const ResourceContentsProperties & get_properties() const { return properties; }
        ResourceContentsProperties & get_mutable_properties() { return properties; }
        void set_properties(const ResourceContentsProperties & value) { this->properties = value; }

        const std::vector<Required> & get_required() const { return required; }
        std::vector<Required> & get_mutable_required() { return required; }
        void set_required(const std::vector<Required> & value) { this->required = value; }

        const AnnotationsType & get_type() const { return type; }
        AnnotationsType & get_mutable_type() { return type; }
        void set_type(const AnnotationsType & value) { this->type = value; }
    };

    class ResourceReferenceProperties {
        public:
        ResourceReferenceProperties() = default;
        virtual ~ResourceReferenceProperties() = default;

        private:
        TypeClass type;
        BlobClass uri;

        public:
        const TypeClass & get_type() const { return type; }
        TypeClass & get_mutable_type() { return type; }
        void set_type(const TypeClass & value) { this->type = value; }

        const BlobClass & get_uri() const { return uri; }
        BlobClass & get_mutable_uri() { return uri; }
        void set_uri(const BlobClass & value) { this->uri = value; }
    };

    class ResourceReference {
        public:
        ResourceReference() = default;
        virtual ~ResourceReference() = default;

        private:
        std::string description;
        ResourceReferenceProperties properties;
        std::vector<std::string> required;
        AnnotationsType type;

        public:
        const std::string & get_description() const { return description; }
        std::string & get_mutable_description() { return description; }
        void set_description(const std::string & value) { this->description = value; }

        const ResourceReferenceProperties & get_properties() const { return properties; }
        ResourceReferenceProperties & get_mutable_properties() { return properties; }
        void set_properties(const ResourceReferenceProperties & value) { this->properties = value; }

        const std::vector<std::string> & get_required() const { return required; }
        std::vector<std::string> & get_mutable_required() { return required; }
        void set_required(const std::vector<std::string> & value) { this->required = value; }

        const AnnotationsType & get_type() const { return type; }
        AnnotationsType & get_mutable_type() { return type; }
        void set_type(const AnnotationsType & value) { this->type = value; }
    };

    class ResourceTemplateProperties {
        public:
        ResourceTemplateProperties() = default;
        virtual ~ResourceTemplateProperties() = default;

        private:
        AnnotationsClass annotations;
        Cursor description;
        Cursor mime_type;
        Cursor name;
        BlobClass uri_template;

        public:
        const AnnotationsClass & get_annotations() const { return annotations; }
        AnnotationsClass & get_mutable_annotations() { return annotations; }
        void set_annotations(const AnnotationsClass & value) { this->annotations = value; }

        const Cursor & get_description() const { return description; }
        Cursor & get_mutable_description() { return description; }
        void set_description(const Cursor & value) { this->description = value; }

        const Cursor & get_mime_type() const { return mime_type; }
        Cursor & get_mutable_mime_type() { return mime_type; }
        void set_mime_type(const Cursor & value) { this->mime_type = value; }

        const Cursor & get_name() const { return name; }
        Cursor & get_mutable_name() { return name; }
        void set_name(const Cursor & value) { this->name = value; }

        const BlobClass & get_uri_template() const { return uri_template; }
        BlobClass & get_mutable_uri_template() { return uri_template; }
        void set_uri_template(const BlobClass & value) { this->uri_template = value; }
    };

    class ResourceTemplate {
        public:
        ResourceTemplate() = default;
        virtual ~ResourceTemplate() = default;

        private:
        std::string description;
        ResourceTemplateProperties properties;
        std::vector<std::string> required;
        AnnotationsType type;

        public:
        const std::string & get_description() const { return description; }
        std::string & get_mutable_description() { return description; }
        void set_description(const std::string & value) { this->description = value; }

        const ResourceTemplateProperties & get_properties() const { return properties; }
        ResourceTemplateProperties & get_mutable_properties() { return properties; }
        void set_properties(const ResourceTemplateProperties & value) { this->properties = value; }

        const std::vector<std::string> & get_required() const { return required; }
        std::vector<std::string> & get_mutable_required() { return required; }
        void set_required(const std::vector<std::string> & value) { this->required = value; }

        const AnnotationsType & get_type() const { return type; }
        AnnotationsType & get_mutable_type() { return type; }
        void set_type(const AnnotationsType & value) { this->type = value; }
    };

    class RootProperties {
        public:
        RootProperties() = default;
        virtual ~RootProperties() = default;

        private:
        Cursor name;
        BlobClass uri;

        public:
        const Cursor & get_name() const { return name; }
        Cursor & get_mutable_name() { return name; }
        void set_name(const Cursor & value) { this->name = value; }

        const BlobClass & get_uri() const { return uri; }
        BlobClass & get_mutable_uri() { return uri; }
        void set_uri(const BlobClass & value) { this->uri = value; }
    };

    class Root {
        public:
        Root() = default;
        virtual ~Root() = default;

        private:
        std::string description;
        RootProperties properties;
        std::vector<Required> required;
        AnnotationsType type;

        public:
        const std::string & get_description() const { return description; }
        std::string & get_mutable_description() { return description; }
        void set_description(const std::string & value) { this->description = value; }

        const RootProperties & get_properties() const { return properties; }
        RootProperties & get_mutable_properties() { return properties; }
        void set_properties(const RootProperties & value) { this->properties = value; }

        const std::vector<Required> & get_required() const { return required; }
        std::vector<Required> & get_mutable_required() { return required; }
        void set_required(const std::vector<Required> & value) { this->required = value; }

        const AnnotationsType & get_type() const { return type; }
        AnnotationsType & get_mutable_type() { return type; }
        void set_type(const AnnotationsType & value) { this->type = value; }
    };

    class ResourcesProperties {
        public:
        ResourcesProperties() = default;
        virtual ~ResourcesProperties() = default;

        private:
        Cursor list_changed;
        Cursor subscribe;

        public:
        const Cursor & get_list_changed() const { return list_changed; }
        Cursor & get_mutable_list_changed() { return list_changed; }
        void set_list_changed(const Cursor & value) { this->list_changed = value; }

        const Cursor & get_subscribe() const { return subscribe; }
        Cursor & get_mutable_subscribe() { return subscribe; }
        void set_subscribe(const Cursor & value) { this->subscribe = value; }
    };

    class Resources {
        public:
        Resources() = default;
        virtual ~Resources() = default;

        private:
        std::string description;
        ResourcesProperties properties;
        AnnotationsType type;

        public:
        const std::string & get_description() const { return description; }
        std::string & get_mutable_description() { return description; }
        void set_description(const std::string & value) { this->description = value; }

        const ResourcesProperties & get_properties() const { return properties; }
        ResourcesProperties & get_mutable_properties() { return properties; }
        void set_properties(const ResourcesProperties & value) { this->properties = value; }

        const AnnotationsType & get_type() const { return type; }
        AnnotationsType & get_mutable_type() { return type; }
        void set_type(const AnnotationsType & value) { this->type = value; }
    };

    class ServerCapabilitiesProperties {
        public:
        ServerCapabilitiesProperties() = default;
        virtual ~ServerCapabilitiesProperties() = default;

        private:
        Sampling completions;
        Experimental experimental;
        Sampling logging;
        Roots prompts;
        Resources resources;
        Roots tools;

        public:
        const Sampling & get_completions() const { return completions; }
        Sampling & get_mutable_completions() { return completions; }
        void set_completions(const Sampling & value) { this->completions = value; }

        const Experimental & get_experimental() const { return experimental; }
        Experimental & get_mutable_experimental() { return experimental; }
        void set_experimental(const Experimental & value) { this->experimental = value; }

        const Sampling & get_logging() const { return logging; }
        Sampling & get_mutable_logging() { return logging; }
        void set_logging(const Sampling & value) { this->logging = value; }

        const Roots & get_prompts() const { return prompts; }
        Roots & get_mutable_prompts() { return prompts; }
        void set_prompts(const Roots & value) { this->prompts = value; }

        const Resources & get_resources() const { return resources; }
        Resources & get_mutable_resources() { return resources; }
        void set_resources(const Resources & value) { this->resources = value; }

        const Roots & get_tools() const { return tools; }
        Roots & get_mutable_tools() { return tools; }
        void set_tools(const Roots & value) { this->tools = value; }
    };

    class ServerCapabilities {
        public:
        ServerCapabilities() = default;
        virtual ~ServerCapabilities() = default;

        private:
        std::string description;
        ServerCapabilitiesProperties properties;
        AnnotationsType type;

        public:
        const std::string & get_description() const { return description; }
        std::string & get_mutable_description() { return description; }
        void set_description(const std::string & value) { this->description = value; }

        const ServerCapabilitiesProperties & get_properties() const { return properties; }
        ServerCapabilitiesProperties & get_mutable_properties() { return properties; }
        void set_properties(const ServerCapabilitiesProperties & value) { this->properties = value; }

        const AnnotationsType & get_type() const { return type; }
        AnnotationsType & get_mutable_type() { return type; }
        void set_type(const AnnotationsType & value) { this->type = value; }
    };

    class Properties1 {
        public:
        Properties1() = default;
        virtual ~Properties1() = default;

        private:
        AnnotationsClass level;

        public:
        const AnnotationsClass & get_level() const { return level; }
        AnnotationsClass & get_mutable_level() { return level; }
        void set_level(const AnnotationsClass & value) { this->level = value; }
    };

    class MischievousParams {
        public:
        MischievousParams() = default;
        virtual ~MischievousParams() = default;

        private:
        Properties1 properties;
        std::vector<std::string> required;
        AnnotationsType type;

        public:
        const Properties1 & get_properties() const { return properties; }
        Properties1 & get_mutable_properties() { return properties; }
        void set_properties(const Properties1 & value) { this->properties = value; }

        const std::vector<std::string> & get_required() const { return required; }
        std::vector<std::string> & get_mutable_required() { return required; }
        void set_required(const std::vector<std::string> & value) { this->required = value; }

        const AnnotationsType & get_type() const { return type; }
        AnnotationsType & get_mutable_type() { return type; }
        void set_type(const AnnotationsType & value) { this->type = value; }
    };

    class SetLevelRequestProperties {
        public:
        SetLevelRequestProperties() = default;
        virtual ~SetLevelRequestProperties() = default;

        private:
        TypeClass method;
        MischievousParams params;

        public:
        const TypeClass & get_method() const { return method; }
        TypeClass & get_mutable_method() { return method; }
        void set_method(const TypeClass & value) { this->method = value; }

        const MischievousParams & get_params() const { return params; }
        MischievousParams & get_mutable_params() { return params; }
        void set_params(const MischievousParams & value) { this->params = value; }
    };

    class SetLevelRequest {
        public:
        SetLevelRequest() = default;
        virtual ~SetLevelRequest() = default;

        private:
        std::string description;
        SetLevelRequestProperties properties;
        std::vector<std::string> required;
        AnnotationsType type;

        public:
        const std::string & get_description() const { return description; }
        std::string & get_mutable_description() { return description; }
        void set_description(const std::string & value) { this->description = value; }

        const SetLevelRequestProperties & get_properties() const { return properties; }
        SetLevelRequestProperties & get_mutable_properties() { return properties; }
        void set_properties(const SetLevelRequestProperties & value) { this->properties = value; }

        const std::vector<std::string> & get_required() const { return required; }
        std::vector<std::string> & get_mutable_required() { return required; }
        void set_required(const std::vector<std::string> & value) { this->required = value; }

        const AnnotationsType & get_type() const { return type; }
        AnnotationsType & get_mutable_type() { return type; }
        void set_type(const AnnotationsType & value) { this->type = value; }
    };

    class TextContentProperties {
        public:
        TextContentProperties() = default;
        virtual ~TextContentProperties() = default;

        private:
        AnnotationsClass annotations;
        Cursor text;
        TypeClass type;

        public:
        const AnnotationsClass & get_annotations() const { return annotations; }
        AnnotationsClass & get_mutable_annotations() { return annotations; }
        void set_annotations(const AnnotationsClass & value) { this->annotations = value; }

        const Cursor & get_text() const { return text; }
        Cursor & get_mutable_text() { return text; }
        void set_text(const Cursor & value) { this->text = value; }

        const TypeClass & get_type() const { return type; }
        TypeClass & get_mutable_type() { return type; }
        void set_type(const TypeClass & value) { this->type = value; }
    };

    class TextContent {
        public:
        TextContent() = default;
        virtual ~TextContent() = default;

        private:
        std::string description;
        TextContentProperties properties;
        std::vector<std::string> required;
        AnnotationsType type;

        public:
        const std::string & get_description() const { return description; }
        std::string & get_mutable_description() { return description; }
        void set_description(const std::string & value) { this->description = value; }

        const TextContentProperties & get_properties() const { return properties; }
        TextContentProperties & get_mutable_properties() { return properties; }
        void set_properties(const TextContentProperties & value) { this->properties = value; }

        const std::vector<std::string> & get_required() const { return required; }
        std::vector<std::string> & get_mutable_required() { return required; }
        void set_required(const std::vector<std::string> & value) { this->required = value; }

        const AnnotationsType & get_type() const { return type; }
        AnnotationsType & get_mutable_type() { return type; }
        void set_type(const AnnotationsType & value) { this->type = value; }
    };

    class TextResourceContentsProperties {
        public:
        TextResourceContentsProperties() = default;
        virtual ~TextResourceContentsProperties() = default;

        private:
        Cursor mime_type;
        Cursor text;
        BlobClass uri;

        public:
        const Cursor & get_mime_type() const { return mime_type; }
        Cursor & get_mutable_mime_type() { return mime_type; }
        void set_mime_type(const Cursor & value) { this->mime_type = value; }

        const Cursor & get_text() const { return text; }
        Cursor & get_mutable_text() { return text; }
        void set_text(const Cursor & value) { this->text = value; }

        const BlobClass & get_uri() const { return uri; }
        BlobClass & get_mutable_uri() { return uri; }
        void set_uri(const BlobClass & value) { this->uri = value; }
    };

    class TextResourceContents {
        public:
        TextResourceContents() = default;
        virtual ~TextResourceContents() = default;

        private:
        TextResourceContentsProperties properties;
        std::vector<std::string> required;
        AnnotationsType type;

        public:
        const TextResourceContentsProperties & get_properties() const { return properties; }
        TextResourceContentsProperties & get_mutable_properties() { return properties; }
        void set_properties(const TextResourceContentsProperties & value) { this->properties = value; }

        const std::vector<std::string> & get_required() const { return required; }
        std::vector<std::string> & get_mutable_required() { return required; }
        void set_required(const std::vector<std::string> & value) { this->required = value; }

        const AnnotationsType & get_type() const { return type; }
        AnnotationsType & get_mutable_type() { return type; }
        void set_type(const AnnotationsType & value) { this->type = value; }
    };

    class PropertiesProperties {
        public:
        PropertiesProperties() = default;
        virtual ~PropertiesProperties() = default;

        private:
        Sampling additional_properties;
        AnnotationsType type;

        public:
        const Sampling & get_additional_properties() const { return additional_properties; }
        Sampling & get_mutable_additional_properties() { return additional_properties; }
        void set_additional_properties(const Sampling & value) { this->additional_properties = value; }

        const AnnotationsType & get_type() const { return type; }
        AnnotationsType & get_mutable_type() { return type; }
        void set_type(const AnnotationsType & value) { this->type = value; }
    };

    class InputSchemaProperties {
        public:
        InputSchemaProperties() = default;
        virtual ~InputSchemaProperties() = default;

        private:
        PropertiesProperties properties;
        StopSequences required;
        TypeClass type;

        public:
        const PropertiesProperties & get_properties() const { return properties; }
        PropertiesProperties & get_mutable_properties() { return properties; }
        void set_properties(const PropertiesProperties & value) { this->properties = value; }

        const StopSequences & get_required() const { return required; }
        StopSequences & get_mutable_required() { return required; }
        void set_required(const StopSequences & value) { this->required = value; }

        const TypeClass & get_type() const { return type; }
        TypeClass & get_mutable_type() { return type; }
        void set_type(const TypeClass & value) { this->type = value; }
    };

    class InputSchema {
        public:
        InputSchema() = default;
        virtual ~InputSchema() = default;

        private:
        std::string description;
        InputSchemaProperties properties;
        std::vector<std::string> required;
        AnnotationsType type;

        public:
        const std::string & get_description() const { return description; }
        std::string & get_mutable_description() { return description; }
        void set_description(const std::string & value) { this->description = value; }

        const InputSchemaProperties & get_properties() const { return properties; }
        InputSchemaProperties & get_mutable_properties() { return properties; }
        void set_properties(const InputSchemaProperties & value) { this->properties = value; }

        const std::vector<std::string> & get_required() const { return required; }
        std::vector<std::string> & get_mutable_required() { return required; }
        void set_required(const std::vector<std::string> & value) { this->required = value; }

        const AnnotationsType & get_type() const { return type; }
        AnnotationsType & get_mutable_type() { return type; }
        void set_type(const AnnotationsType & value) { this->type = value; }
    };

    class ToolProperties {
        public:
        ToolProperties() = default;
        virtual ~ToolProperties() = default;

        private:
        AnnotationsClass annotations;
        Cursor description;
        InputSchema input_schema;
        Cursor name;

        public:
        const AnnotationsClass & get_annotations() const { return annotations; }
        AnnotationsClass & get_mutable_annotations() { return annotations; }
        void set_annotations(const AnnotationsClass & value) { this->annotations = value; }

        const Cursor & get_description() const { return description; }
        Cursor & get_mutable_description() { return description; }
        void set_description(const Cursor & value) { this->description = value; }

        const InputSchema & get_input_schema() const { return input_schema; }
        InputSchema & get_mutable_input_schema() { return input_schema; }
        void set_input_schema(const InputSchema & value) { this->input_schema = value; }

        const Cursor & get_name() const { return name; }
        Cursor & get_mutable_name() { return name; }
        void set_name(const Cursor & value) { this->name = value; }
    };

    class Tool {
        public:
        Tool() = default;
        virtual ~Tool() = default;

        private:
        std::string description;
        ToolProperties properties;
        std::vector<std::string> required;
        AnnotationsType type;

        public:
        const std::string & get_description() const { return description; }
        std::string & get_mutable_description() { return description; }
        void set_description(const std::string & value) { this->description = value; }

        const ToolProperties & get_properties() const { return properties; }
        ToolProperties & get_mutable_properties() { return properties; }
        void set_properties(const ToolProperties & value) { this->properties = value; }

        const std::vector<std::string> & get_required() const { return required; }
        std::vector<std::string> & get_mutable_required() { return required; }
        void set_required(const std::vector<std::string> & value) { this->required = value; }

        const AnnotationsType & get_type() const { return type; }
        AnnotationsType & get_mutable_type() { return type; }
        void set_type(const AnnotationsType & value) { this->type = value; }
    };

    class ToolAnnotationsProperties {
        public:
        ToolAnnotationsProperties() = default;
        virtual ~ToolAnnotationsProperties() = default;

        private:
        Cursor destructive_hint;
        Cursor idempotent_hint;
        Cursor open_world_hint;
        Cursor read_only_hint;
        Cursor title;

        public:
        const Cursor & get_destructive_hint() const { return destructive_hint; }
        Cursor & get_mutable_destructive_hint() { return destructive_hint; }
        void set_destructive_hint(const Cursor & value) { this->destructive_hint = value; }

        const Cursor & get_idempotent_hint() const { return idempotent_hint; }
        Cursor & get_mutable_idempotent_hint() { return idempotent_hint; }
        void set_idempotent_hint(const Cursor & value) { this->idempotent_hint = value; }

        const Cursor & get_open_world_hint() const { return open_world_hint; }
        Cursor & get_mutable_open_world_hint() { return open_world_hint; }
        void set_open_world_hint(const Cursor & value) { this->open_world_hint = value; }

        const Cursor & get_read_only_hint() const { return read_only_hint; }
        Cursor & get_mutable_read_only_hint() { return read_only_hint; }
        void set_read_only_hint(const Cursor & value) { this->read_only_hint = value; }

        const Cursor & get_title() const { return title; }
        Cursor & get_mutable_title() { return title; }
        void set_title(const Cursor & value) { this->title = value; }
    };

    class ToolAnnotations {
        public:
        ToolAnnotations() = default;
        virtual ~ToolAnnotations() = default;

        private:
        std::string description;
        ToolAnnotationsProperties properties;
        AnnotationsType type;

        public:
        const std::string & get_description() const { return description; }
        std::string & get_mutable_description() { return description; }
        void set_description(const std::string & value) { this->description = value; }

        const ToolAnnotationsProperties & get_properties() const { return properties; }
        ToolAnnotationsProperties & get_mutable_properties() { return properties; }
        void set_properties(const ToolAnnotationsProperties & value) { this->properties = value; }

        const AnnotationsType & get_type() const { return type; }
        AnnotationsType & get_mutable_type() { return type; }
        void set_type(const AnnotationsType & value) { this->type = value; }
    };

    class Definitions {
        public:
        Definitions() = default;
        virtual ~Definitions() = default;

        private:
        Annotations annotations;
        Content audio_content;
        BlobResourceContents blob_resource_contents;
        CallToolRequest call_tool_request;
        CallToolResult call_tool_result;
        CancelledNotification cancelled_notification;
        ClientCapabilities client_capabilities;
        ClientNotification client_notification;
        ClientNotification client_request;
        ClientNotification client_result;
        CompleteRequest complete_request;
        CompleteResult complete_result;
        CreateMessageRequest create_message_request;
        CreateMessageResult create_message_result;
        Cursor cursor;
        EmbeddedResource embedded_resource;
        EmptyResult empty_result;
        GetPromptRequest get_prompt_request;
        GetPromptResult get_prompt_result;
        Content image_content;
        Implementation implementation;
        InitializeRequest initialize_request;
        InitializeResult initialize_result;
        EdNotification initialized_notification;
        JsonrpcBatchRequest jsonrpc_batch_request;
        JsonrpcBatchRequest jsonrpc_batch_response;
        JsonrpcError jsonrpc_error;
        JsonrpcMessage jsonrpc_message;
        JsonrpcNotification jsonrpc_notification;
        JsonrpcRequest jsonrpc_request;
        JsonrpcResponse jsonrpc_response;
        ListSRequest list_prompts_request;
        ListPromptsResult list_prompts_result;
        ListSRequest list_resource_templates_request;
        ListResourceTemplatesResult list_resource_templates_result;
        ListSRequest list_resources_request;
        ListResourcesResult list_resources_result;
        Request list_roots_request;
        ListRootsResult list_roots_result;
        ListSRequest list_tools_request;
        ListToolsResult list_tools_result;
        LoggingLevel logging_level;
        LoggingMessageNotification logging_message_notification;
        ModelHint model_hint;
        ModelPreferences model_preferences;
        Notification notification;
        PaginatedRequest paginated_request;
        PaginatedResult paginated_result;
        Request ping_request;
        ProgressNotification progress_notification;
        ProgressToken progress_token;
        Prompt prompt;
        PromptArgument prompt_argument;
        EdNotification prompt_list_changed_notification;
        Message prompt_message;
        PromptReference prompt_reference;
        ReadResourceRequest read_resource_request;
        ReadResourceResult read_resource_result;
        RequestClass request;
        ProgressToken request_id;
        Resource resource;
        ResourceContents resource_contents;
        EdNotification resource_list_changed_notification;
        ResourceReference resource_reference;
        ResourceTemplate resource_template;
        ReadResourceRequest resource_updated_notification;
        Result result;
        LoggingLevel role;
        Root root;
        EdNotification roots_list_changed_notification;
        Message sampling_message;
        ServerCapabilities server_capabilities;
        ClientNotification server_notification;
        ClientNotification server_request;
        ClientNotification server_result;
        SetLevelRequest set_level_request;
        ReadResourceRequest subscribe_request;
        TextContent text_content;
        TextResourceContents text_resource_contents;
        Tool tool;
        ToolAnnotations tool_annotations;
        EdNotification tool_list_changed_notification;
        ReadResourceRequest unsubscribe_request;

        public:
        const Annotations & get_annotations() const { return annotations; }
        Annotations & get_mutable_annotations() { return annotations; }
        void set_annotations(const Annotations & value) { this->annotations = value; }

        const Content & get_audio_content() const { return audio_content; }
        Content & get_mutable_audio_content() { return audio_content; }
        void set_audio_content(const Content & value) { this->audio_content = value; }

        const BlobResourceContents & get_blob_resource_contents() const { return blob_resource_contents; }
        BlobResourceContents & get_mutable_blob_resource_contents() { return blob_resource_contents; }
        void set_blob_resource_contents(const BlobResourceContents & value) { this->blob_resource_contents = value; }

        const CallToolRequest & get_call_tool_request() const { return call_tool_request; }
        CallToolRequest & get_mutable_call_tool_request() { return call_tool_request; }
        void set_call_tool_request(const CallToolRequest & value) { this->call_tool_request = value; }

        const CallToolResult & get_call_tool_result() const { return call_tool_result; }
        CallToolResult & get_mutable_call_tool_result() { return call_tool_result; }
        void set_call_tool_result(const CallToolResult & value) { this->call_tool_result = value; }

        const CancelledNotification & get_cancelled_notification() const { return cancelled_notification; }
        CancelledNotification & get_mutable_cancelled_notification() { return cancelled_notification; }
        void set_cancelled_notification(const CancelledNotification & value) { this->cancelled_notification = value; }

        const ClientCapabilities & get_client_capabilities() const { return client_capabilities; }
        ClientCapabilities & get_mutable_client_capabilities() { return client_capabilities; }
        void set_client_capabilities(const ClientCapabilities & value) { this->client_capabilities = value; }

        const ClientNotification & get_client_notification() const { return client_notification; }
        ClientNotification & get_mutable_client_notification() { return client_notification; }
        void set_client_notification(const ClientNotification & value) { this->client_notification = value; }

        const ClientNotification & get_client_request() const { return client_request; }
        ClientNotification & get_mutable_client_request() { return client_request; }
        void set_client_request(const ClientNotification & value) { this->client_request = value; }

        const ClientNotification & get_client_result() const { return client_result; }
        ClientNotification & get_mutable_client_result() { return client_result; }
        void set_client_result(const ClientNotification & value) { this->client_result = value; }

        const CompleteRequest & get_complete_request() const { return complete_request; }
        CompleteRequest & get_mutable_complete_request() { return complete_request; }
        void set_complete_request(const CompleteRequest & value) { this->complete_request = value; }

        const CompleteResult & get_complete_result() const { return complete_result; }
        CompleteResult & get_mutable_complete_result() { return complete_result; }
        void set_complete_result(const CompleteResult & value) { this->complete_result = value; }

        const CreateMessageRequest & get_create_message_request() const { return create_message_request; }
        CreateMessageRequest & get_mutable_create_message_request() { return create_message_request; }
        void set_create_message_request(const CreateMessageRequest & value) { this->create_message_request = value; }

        const CreateMessageResult & get_create_message_result() const { return create_message_result; }
        CreateMessageResult & get_mutable_create_message_result() { return create_message_result; }
        void set_create_message_result(const CreateMessageResult & value) { this->create_message_result = value; }

        const Cursor & get_cursor() const { return cursor; }
        Cursor & get_mutable_cursor() { return cursor; }
        void set_cursor(const Cursor & value) { this->cursor = value; }

        const EmbeddedResource & get_embedded_resource() const { return embedded_resource; }
        EmbeddedResource & get_mutable_embedded_resource() { return embedded_resource; }
        void set_embedded_resource(const EmbeddedResource & value) { this->embedded_resource = value; }

        const EmptyResult & get_empty_result() const { return empty_result; }
        EmptyResult & get_mutable_empty_result() { return empty_result; }
        void set_empty_result(const EmptyResult & value) { this->empty_result = value; }

        const GetPromptRequest & get_get_prompt_request() const { return get_prompt_request; }
        GetPromptRequest & get_mutable_get_prompt_request() { return get_prompt_request; }
        void set_get_prompt_request(const GetPromptRequest & value) { this->get_prompt_request = value; }

        const GetPromptResult & get_get_prompt_result() const { return get_prompt_result; }
        GetPromptResult & get_mutable_get_prompt_result() { return get_prompt_result; }
        void set_get_prompt_result(const GetPromptResult & value) { this->get_prompt_result = value; }

        const Content & get_image_content() const { return image_content; }
        Content & get_mutable_image_content() { return image_content; }
        void set_image_content(const Content & value) { this->image_content = value; }

        const Implementation & get_implementation() const { return implementation; }
        Implementation & get_mutable_implementation() { return implementation; }
        void set_implementation(const Implementation & value) { this->implementation = value; }

        const InitializeRequest & get_initialize_request() const { return initialize_request; }
        InitializeRequest & get_mutable_initialize_request() { return initialize_request; }
        void set_initialize_request(const InitializeRequest & value) { this->initialize_request = value; }

        const InitializeResult & get_initialize_result() const { return initialize_result; }
        InitializeResult & get_mutable_initialize_result() { return initialize_result; }
        void set_initialize_result(const InitializeResult & value) { this->initialize_result = value; }

        const EdNotification & get_initialized_notification() const { return initialized_notification; }
        EdNotification & get_mutable_initialized_notification() { return initialized_notification; }
        void set_initialized_notification(const EdNotification & value) { this->initialized_notification = value; }

        const JsonrpcBatchRequest & get_jsonrpc_batch_request() const { return jsonrpc_batch_request; }
        JsonrpcBatchRequest & get_mutable_jsonrpc_batch_request() { return jsonrpc_batch_request; }
        void set_jsonrpc_batch_request(const JsonrpcBatchRequest & value) { this->jsonrpc_batch_request = value; }

        const JsonrpcBatchRequest & get_jsonrpc_batch_response() const { return jsonrpc_batch_response; }
        JsonrpcBatchRequest & get_mutable_jsonrpc_batch_response() { return jsonrpc_batch_response; }
        void set_jsonrpc_batch_response(const JsonrpcBatchRequest & value) { this->jsonrpc_batch_response = value; }

        const JsonrpcError & get_jsonrpc_error() const { return jsonrpc_error; }
        JsonrpcError & get_mutable_jsonrpc_error() { return jsonrpc_error; }
        void set_jsonrpc_error(const JsonrpcError & value) { this->jsonrpc_error = value; }

        const JsonrpcMessage & get_jsonrpc_message() const { return jsonrpc_message; }
        JsonrpcMessage & get_mutable_jsonrpc_message() { return jsonrpc_message; }
        void set_jsonrpc_message(const JsonrpcMessage & value) { this->jsonrpc_message = value; }

        const JsonrpcNotification & get_jsonrpc_notification() const { return jsonrpc_notification; }
        JsonrpcNotification & get_mutable_jsonrpc_notification() { return jsonrpc_notification; }
        void set_jsonrpc_notification(const JsonrpcNotification & value) { this->jsonrpc_notification = value; }

        const JsonrpcRequest & get_jsonrpc_request() const { return jsonrpc_request; }
        JsonrpcRequest & get_mutable_jsonrpc_request() { return jsonrpc_request; }
        void set_jsonrpc_request(const JsonrpcRequest & value) { this->jsonrpc_request = value; }

        const JsonrpcResponse & get_jsonrpc_response() const { return jsonrpc_response; }
        JsonrpcResponse & get_mutable_jsonrpc_response() { return jsonrpc_response; }
        void set_jsonrpc_response(const JsonrpcResponse & value) { this->jsonrpc_response = value; }

        const ListSRequest & get_list_prompts_request() const { return list_prompts_request; }
        ListSRequest & get_mutable_list_prompts_request() { return list_prompts_request; }
        void set_list_prompts_request(const ListSRequest & value) { this->list_prompts_request = value; }

        const ListPromptsResult & get_list_prompts_result() const { return list_prompts_result; }
        ListPromptsResult & get_mutable_list_prompts_result() { return list_prompts_result; }
        void set_list_prompts_result(const ListPromptsResult & value) { this->list_prompts_result = value; }

        const ListSRequest & get_list_resource_templates_request() const { return list_resource_templates_request; }
        ListSRequest & get_mutable_list_resource_templates_request() { return list_resource_templates_request; }
        void set_list_resource_templates_request(const ListSRequest & value) { this->list_resource_templates_request = value; }

        const ListResourceTemplatesResult & get_list_resource_templates_result() const { return list_resource_templates_result; }
        ListResourceTemplatesResult & get_mutable_list_resource_templates_result() { return list_resource_templates_result; }
        void set_list_resource_templates_result(const ListResourceTemplatesResult & value) { this->list_resource_templates_result = value; }

        const ListSRequest & get_list_resources_request() const { return list_resources_request; }
        ListSRequest & get_mutable_list_resources_request() { return list_resources_request; }
        void set_list_resources_request(const ListSRequest & value) { this->list_resources_request = value; }

        const ListResourcesResult & get_list_resources_result() const { return list_resources_result; }
        ListResourcesResult & get_mutable_list_resources_result() { return list_resources_result; }
        void set_list_resources_result(const ListResourcesResult & value) { this->list_resources_result = value; }

        const Request & get_list_roots_request() const { return list_roots_request; }
        Request & get_mutable_list_roots_request() { return list_roots_request; }
        void set_list_roots_request(const Request & value) { this->list_roots_request = value; }

        const ListRootsResult & get_list_roots_result() const { return list_roots_result; }
        ListRootsResult & get_mutable_list_roots_result() { return list_roots_result; }
        void set_list_roots_result(const ListRootsResult & value) { this->list_roots_result = value; }

        const ListSRequest & get_list_tools_request() const { return list_tools_request; }
        ListSRequest & get_mutable_list_tools_request() { return list_tools_request; }
        void set_list_tools_request(const ListSRequest & value) { this->list_tools_request = value; }

        const ListToolsResult & get_list_tools_result() const { return list_tools_result; }
        ListToolsResult & get_mutable_list_tools_result() { return list_tools_result; }
        void set_list_tools_result(const ListToolsResult & value) { this->list_tools_result = value; }

        const LoggingLevel & get_logging_level() const { return logging_level; }
        LoggingLevel & get_mutable_logging_level() { return logging_level; }
        void set_logging_level(const LoggingLevel & value) { this->logging_level = value; }

        const LoggingMessageNotification & get_logging_message_notification() const { return logging_message_notification; }
        LoggingMessageNotification & get_mutable_logging_message_notification() { return logging_message_notification; }
        void set_logging_message_notification(const LoggingMessageNotification & value) { this->logging_message_notification = value; }

        const ModelHint & get_model_hint() const { return model_hint; }
        ModelHint & get_mutable_model_hint() { return model_hint; }
        void set_model_hint(const ModelHint & value) { this->model_hint = value; }

        const ModelPreferences & get_model_preferences() const { return model_preferences; }
        ModelPreferences & get_mutable_model_preferences() { return model_preferences; }
        void set_model_preferences(const ModelPreferences & value) { this->model_preferences = value; }

        const Notification & get_notification() const { return notification; }
        Notification & get_mutable_notification() { return notification; }
        void set_notification(const Notification & value) { this->notification = value; }

        const PaginatedRequest & get_paginated_request() const { return paginated_request; }
        PaginatedRequest & get_mutable_paginated_request() { return paginated_request; }
        void set_paginated_request(const PaginatedRequest & value) { this->paginated_request = value; }

        const PaginatedResult & get_paginated_result() const { return paginated_result; }
        PaginatedResult & get_mutable_paginated_result() { return paginated_result; }
        void set_paginated_result(const PaginatedResult & value) { this->paginated_result = value; }

        const Request & get_ping_request() const { return ping_request; }
        Request & get_mutable_ping_request() { return ping_request; }
        void set_ping_request(const Request & value) { this->ping_request = value; }

        const ProgressNotification & get_progress_notification() const { return progress_notification; }
        ProgressNotification & get_mutable_progress_notification() { return progress_notification; }
        void set_progress_notification(const ProgressNotification & value) { this->progress_notification = value; }

        const ProgressToken & get_progress_token() const { return progress_token; }
        ProgressToken & get_mutable_progress_token() { return progress_token; }
        void set_progress_token(const ProgressToken & value) { this->progress_token = value; }

        const Prompt & get_prompt() const { return prompt; }
        Prompt & get_mutable_prompt() { return prompt; }
        void set_prompt(const Prompt & value) { this->prompt = value; }

        const PromptArgument & get_prompt_argument() const { return prompt_argument; }
        PromptArgument & get_mutable_prompt_argument() { return prompt_argument; }
        void set_prompt_argument(const PromptArgument & value) { this->prompt_argument = value; }

        const EdNotification & get_prompt_list_changed_notification() const { return prompt_list_changed_notification; }
        EdNotification & get_mutable_prompt_list_changed_notification() { return prompt_list_changed_notification; }
        void set_prompt_list_changed_notification(const EdNotification & value) { this->prompt_list_changed_notification = value; }

        const Message & get_prompt_message() const { return prompt_message; }
        Message & get_mutable_prompt_message() { return prompt_message; }
        void set_prompt_message(const Message & value) { this->prompt_message = value; }

        const PromptReference & get_prompt_reference() const { return prompt_reference; }
        PromptReference & get_mutable_prompt_reference() { return prompt_reference; }
        void set_prompt_reference(const PromptReference & value) { this->prompt_reference = value; }

        const ReadResourceRequest & get_read_resource_request() const { return read_resource_request; }
        ReadResourceRequest & get_mutable_read_resource_request() { return read_resource_request; }
        void set_read_resource_request(const ReadResourceRequest & value) { this->read_resource_request = value; }

        const ReadResourceResult & get_read_resource_result() const { return read_resource_result; }
        ReadResourceResult & get_mutable_read_resource_result() { return read_resource_result; }
        void set_read_resource_result(const ReadResourceResult & value) { this->read_resource_result = value; }

        const RequestClass & get_request() const { return request; }
        RequestClass & get_mutable_request() { return request; }
        void set_request(const RequestClass & value) { this->request = value; }

        const ProgressToken & get_request_id() const { return request_id; }
        ProgressToken & get_mutable_request_id() { return request_id; }
        void set_request_id(const ProgressToken & value) { this->request_id = value; }

        const Resource & get_resource() const { return resource; }
        Resource & get_mutable_resource() { return resource; }
        void set_resource(const Resource & value) { this->resource = value; }

        const ResourceContents & get_resource_contents() const { return resource_contents; }
        ResourceContents & get_mutable_resource_contents() { return resource_contents; }
        void set_resource_contents(const ResourceContents & value) { this->resource_contents = value; }

        const EdNotification & get_resource_list_changed_notification() const { return resource_list_changed_notification; }
        EdNotification & get_mutable_resource_list_changed_notification() { return resource_list_changed_notification; }
        void set_resource_list_changed_notification(const EdNotification & value) { this->resource_list_changed_notification = value; }

        const ResourceReference & get_resource_reference() const { return resource_reference; }
        ResourceReference & get_mutable_resource_reference() { return resource_reference; }
        void set_resource_reference(const ResourceReference & value) { this->resource_reference = value; }

        const ResourceTemplate & get_resource_template() const { return resource_template; }
        ResourceTemplate & get_mutable_resource_template() { return resource_template; }
        void set_resource_template(const ResourceTemplate & value) { this->resource_template = value; }

        const ReadResourceRequest & get_resource_updated_notification() const { return resource_updated_notification; }
        ReadResourceRequest & get_mutable_resource_updated_notification() { return resource_updated_notification; }
        void set_resource_updated_notification(const ReadResourceRequest & value) { this->resource_updated_notification = value; }

        const Result & get_result() const { return result; }
        Result & get_mutable_result() { return result; }
        void set_result(const Result & value) { this->result = value; }

        const LoggingLevel & get_role() const { return role; }
        LoggingLevel & get_mutable_role() { return role; }
        void set_role(const LoggingLevel & value) { this->role = value; }

        const Root & get_root() const { return root; }
        Root & get_mutable_root() { return root; }
        void set_root(const Root & value) { this->root = value; }

        const EdNotification & get_roots_list_changed_notification() const { return roots_list_changed_notification; }
        EdNotification & get_mutable_roots_list_changed_notification() { return roots_list_changed_notification; }
        void set_roots_list_changed_notification(const EdNotification & value) { this->roots_list_changed_notification = value; }

        const Message & get_sampling_message() const { return sampling_message; }
        Message & get_mutable_sampling_message() { return sampling_message; }
        void set_sampling_message(const Message & value) { this->sampling_message = value; }

        const ServerCapabilities & get_server_capabilities() const { return server_capabilities; }
        ServerCapabilities & get_mutable_server_capabilities() { return server_capabilities; }
        void set_server_capabilities(const ServerCapabilities & value) { this->server_capabilities = value; }

        const ClientNotification & get_server_notification() const { return server_notification; }
        ClientNotification & get_mutable_server_notification() { return server_notification; }
        void set_server_notification(const ClientNotification & value) { this->server_notification = value; }

        const ClientNotification & get_server_request() const { return server_request; }
        ClientNotification & get_mutable_server_request() { return server_request; }
        void set_server_request(const ClientNotification & value) { this->server_request = value; }

        const ClientNotification & get_server_result() const { return server_result; }
        ClientNotification & get_mutable_server_result() { return server_result; }
        void set_server_result(const ClientNotification & value) { this->server_result = value; }

        const SetLevelRequest & get_set_level_request() const { return set_level_request; }
        SetLevelRequest & get_mutable_set_level_request() { return set_level_request; }
        void set_set_level_request(const SetLevelRequest & value) { this->set_level_request = value; }

        const ReadResourceRequest & get_subscribe_request() const { return subscribe_request; }
        ReadResourceRequest & get_mutable_subscribe_request() { return subscribe_request; }
        void set_subscribe_request(const ReadResourceRequest & value) { this->subscribe_request = value; }

        const TextContent & get_text_content() const { return text_content; }
        TextContent & get_mutable_text_content() { return text_content; }
        void set_text_content(const TextContent & value) { this->text_content = value; }

        const TextResourceContents & get_text_resource_contents() const { return text_resource_contents; }
        TextResourceContents & get_mutable_text_resource_contents() { return text_resource_contents; }
        void set_text_resource_contents(const TextResourceContents & value) { this->text_resource_contents = value; }

        const Tool & get_tool() const { return tool; }
        Tool & get_mutable_tool() { return tool; }
        void set_tool(const Tool & value) { this->tool = value; }

        const ToolAnnotations & get_tool_annotations() const { return tool_annotations; }
        ToolAnnotations & get_mutable_tool_annotations() { return tool_annotations; }
        void set_tool_annotations(const ToolAnnotations & value) { this->tool_annotations = value; }

        const EdNotification & get_tool_list_changed_notification() const { return tool_list_changed_notification; }
        EdNotification & get_mutable_tool_list_changed_notification() { return tool_list_changed_notification; }
        void set_tool_list_changed_notification(const EdNotification & value) { this->tool_list_changed_notification = value; }

        const ReadResourceRequest & get_unsubscribe_request() const { return unsubscribe_request; }
        ReadResourceRequest & get_mutable_unsubscribe_request() { return unsubscribe_request; }
        void set_unsubscribe_request(const ReadResourceRequest & value) { this->unsubscribe_request = value; }
    };

    class Schema {
        public:
        Schema() = default;
        virtual ~Schema() = default;

        private:
        std::string schema;
        Definitions definitions;

        public:
        const std::string & get_schema() const { return schema; }
        std::string & get_mutable_schema() { return schema; }
        void set_schema(const std::string & value) { this->schema = value; }

        const Definitions & get_definitions() const { return definitions; }
        Definitions & get_mutable_definitions() { return definitions; }
        void set_definitions(const Definitions & value) { this->definitions = value; }
    };
}

namespace quicktype {
    void from_json(const json & j, EmptyResult & x);
    void to_json(json & j, const EmptyResult & x);

    void from_json(const json & j, Audience & x);
    void to_json(json & j, const Audience & x);

    void from_json(const json & j, Priority & x);
    void to_json(json & j, const Priority & x);

    void from_json(const json & j, AnnotationsProperties & x);
    void to_json(json & j, const AnnotationsProperties & x);

    void from_json(const json & j, Annotations & x);
    void to_json(json & j, const Annotations & x);

    void from_json(const json & j, AnnotationsClass & x);
    void to_json(json & j, const AnnotationsClass & x);

    void from_json(const json & j, BlobClass & x);
    void to_json(json & j, const BlobClass & x);

    void from_json(const json & j, Cursor & x);
    void to_json(json & j, const Cursor & x);

    void from_json(const json & j, TypeClass & x);
    void to_json(json & j, const TypeClass & x);

    void from_json(const json & j, AudioContentProperties & x);
    void to_json(json & j, const AudioContentProperties & x);

    void from_json(const json & j, Content & x);
    void to_json(json & j, const Content & x);

    void from_json(const json & j, BlobResourceContentsProperties & x);
    void to_json(json & j, const BlobResourceContentsProperties & x);

    void from_json(const json & j, BlobResourceContents & x);
    void to_json(json & j, const BlobResourceContents & x);

    void from_json(const json & j, AdditionalPropertiesClass & x);
    void to_json(json & j, const AdditionalPropertiesClass & x);

    void from_json(const json & j, PurpleArguments & x);
    void to_json(json & j, const PurpleArguments & x);

    void from_json(const json & j, Name & x);
    void to_json(json & j, const Name & x);

    void from_json(const json & j, PurpleProperties & x);
    void to_json(json & j, const PurpleProperties & x);

    void from_json(const json & j, PurpleParams & x);
    void to_json(json & j, const PurpleParams & x);

    void from_json(const json & j, CallToolRequestProperties & x);
    void to_json(json & j, const CallToolRequestProperties & x);

    void from_json(const json & j, CallToolRequest & x);
    void to_json(json & j, const CallToolRequest & x);

    void from_json(const json & j, ClientNotification & x);
    void to_json(json & j, const ClientNotification & x);

    void from_json(const json & j, ContentClass & x);
    void to_json(json & j, const ContentClass & x);

    void from_json(const json & j, PurpleMeta & x);
    void to_json(json & j, const PurpleMeta & x);

    void from_json(const json & j, CallToolResultProperties & x);
    void to_json(json & j, const CallToolResultProperties & x);

    void from_json(const json & j, CallToolResult & x);
    void to_json(json & j, const CallToolResult & x);

    void from_json(const json & j, FluffyProperties & x);
    void to_json(json & j, const FluffyProperties & x);

    void from_json(const json & j, FluffyParams & x);
    void to_json(json & j, const FluffyParams & x);

    void from_json(const json & j, CancelledNotificationProperties & x);
    void to_json(json & j, const CancelledNotificationProperties & x);

    void from_json(const json & j, CancelledNotification & x);
    void to_json(json & j, const CancelledNotification & x);

    void from_json(const json & j, Sampling & x);
    void to_json(json & j, const Sampling & x);

    void from_json(const json & j, Experimental & x);
    void to_json(json & j, const Experimental & x);

    void from_json(const json & j, RootsProperties & x);
    void to_json(json & j, const RootsProperties & x);

    void from_json(const json & j, Roots & x);
    void to_json(json & j, const Roots & x);

    void from_json(const json & j, ClientCapabilitiesProperties & x);
    void to_json(json & j, const ClientCapabilitiesProperties & x);

    void from_json(const json & j, ClientCapabilities & x);
    void to_json(json & j, const ClientCapabilities & x);

    void from_json(const json & j, ArgumentProperties & x);
    void to_json(json & j, const ArgumentProperties & x);

    void from_json(const json & j, Argument & x);
    void to_json(json & j, const Argument & x);

    void from_json(const json & j, TentacledProperties & x);
    void to_json(json & j, const TentacledProperties & x);

    void from_json(const json & j, TentacledParams & x);
    void to_json(json & j, const TentacledParams & x);

    void from_json(const json & j, CompleteRequestProperties & x);
    void to_json(json & j, const CompleteRequestProperties & x);

    void from_json(const json & j, CompleteRequest & x);
    void to_json(json & j, const CompleteRequest & x);

    void from_json(const json & j, Values & x);
    void to_json(json & j, const Values & x);

    void from_json(const json & j, CompletionProperties & x);
    void to_json(json & j, const CompletionProperties & x);

    void from_json(const json & j, Completion & x);
    void to_json(json & j, const Completion & x);

    void from_json(const json & j, CompleteResultProperties & x);
    void to_json(json & j, const CompleteResultProperties & x);

    void from_json(const json & j, CompleteResult & x);
    void to_json(json & j, const CompleteResult & x);

    void from_json(const json & j, LoggingLevel & x);
    void to_json(json & j, const LoggingLevel & x);

    void from_json(const json & j, Messages & x);
    void to_json(json & j, const Messages & x);

    void from_json(const json & j, StopSequences & x);
    void to_json(json & j, const StopSequences & x);

    void from_json(const json & j, StickyProperties & x);
    void to_json(json & j, const StickyProperties & x);

    void from_json(const json & j, StickyParams & x);
    void to_json(json & j, const StickyParams & x);

    void from_json(const json & j, CreateMessageRequestProperties & x);
    void to_json(json & j, const CreateMessageRequestProperties & x);

    void from_json(const json & j, CreateMessageRequest & x);
    void to_json(json & j, const CreateMessageRequest & x);

    void from_json(const json & j, CreateMessageResultProperties & x);
    void to_json(json & j, const CreateMessageResultProperties & x);

    void from_json(const json & j, CreateMessageResult & x);
    void to_json(json & j, const CreateMessageResult & x);

    void from_json(const json & j, EmbeddedResourceProperties & x);
    void to_json(json & j, const EmbeddedResourceProperties & x);

    void from_json(const json & j, EmbeddedResource & x);
    void to_json(json & j, const EmbeddedResource & x);

    void from_json(const json & j, FluffyArguments & x);
    void to_json(json & j, const FluffyArguments & x);

    void from_json(const json & j, IndigoProperties & x);
    void to_json(json & j, const IndigoProperties & x);

    void from_json(const json & j, IndigoParams & x);
    void to_json(json & j, const IndigoParams & x);

    void from_json(const json & j, GetPromptRequestProperties & x);
    void to_json(json & j, const GetPromptRequestProperties & x);

    void from_json(const json & j, GetPromptRequest & x);
    void to_json(json & j, const GetPromptRequest & x);

    void from_json(const json & j, GetPromptResultProperties & x);
    void to_json(json & j, const GetPromptResultProperties & x);

    void from_json(const json & j, GetPromptResult & x);
    void to_json(json & j, const GetPromptResult & x);

    void from_json(const json & j, ImplementationProperties & x);
    void to_json(json & j, const ImplementationProperties & x);

    void from_json(const json & j, Implementation & x);
    void to_json(json & j, const Implementation & x);

    void from_json(const json & j, IndecentProperties & x);
    void to_json(json & j, const IndecentProperties & x);

    void from_json(const json & j, IndecentParams & x);
    void to_json(json & j, const IndecentParams & x);

    void from_json(const json & j, InitializeRequestProperties & x);
    void to_json(json & j, const InitializeRequestProperties & x);

    void from_json(const json & j, InitializeRequest & x);
    void to_json(json & j, const InitializeRequest & x);

    void from_json(const json & j, InitializeResultProperties & x);
    void to_json(json & j, const InitializeResultProperties & x);

    void from_json(const json & j, InitializeResult & x);
    void to_json(json & j, const InitializeResult & x);

    void from_json(const json & j, HilariousProperties & x);
    void to_json(json & j, const HilariousProperties & x);

    void from_json(const json & j, Result & x);
    void to_json(json & j, const Result & x);

    void from_json(const json & j, InitializedNotificationProperties & x);
    void to_json(json & j, const InitializedNotificationProperties & x);

    void from_json(const json & j, EdNotification & x);
    void to_json(json & j, const EdNotification & x);

    void from_json(const json & j, JsonrpcBatchRequest & x);
    void to_json(json & j, const JsonrpcBatchRequest & x);

    void from_json(const json & j, PurpleData & x);
    void to_json(json & j, const PurpleData & x);

    void from_json(const json & j, ErrorProperties & x);
    void to_json(json & j, const ErrorProperties & x);

    void from_json(const json & j, Error & x);
    void to_json(json & j, const Error & x);

    void from_json(const json & j, JsonrpcErrorProperties & x);
    void to_json(json & j, const JsonrpcErrorProperties & x);

    void from_json(const json & j, JsonrpcError & x);
    void to_json(json & j, const JsonrpcError & x);

    void from_json(const json & j, JsonrpcMessage & x);
    void to_json(json & j, const JsonrpcMessage & x);

    void from_json(const json & j, JsonrpcNotificationProperties & x);
    void to_json(json & j, const JsonrpcNotificationProperties & x);

    void from_json(const json & j, JsonrpcNotification & x);
    void to_json(json & j, const JsonrpcNotification & x);

    void from_json(const json & j, CunningProperties & x);
    void to_json(json & j, const CunningProperties & x);

    void from_json(const json & j, FluffyMeta & x);
    void to_json(json & j, const FluffyMeta & x);

    void from_json(const json & j, AmbitiousProperties & x);
    void to_json(json & j, const AmbitiousProperties & x);

    void from_json(const json & j, HilariousParams & x);
    void to_json(json & j, const HilariousParams & x);

    void from_json(const json & j, JsonrpcRequestProperties & x);
    void to_json(json & j, const JsonrpcRequestProperties & x);

    void from_json(const json & j, JsonrpcRequest & x);
    void to_json(json & j, const JsonrpcRequest & x);

    void from_json(const json & j, JsonrpcResponseProperties & x);
    void to_json(json & j, const JsonrpcResponseProperties & x);

    void from_json(const json & j, JsonrpcResponse & x);
    void to_json(json & j, const JsonrpcResponse & x);

    void from_json(const json & j, MagentaProperties & x);
    void to_json(json & j, const MagentaProperties & x);

    void from_json(const json & j, AmbitiousParams & x);
    void to_json(json & j, const AmbitiousParams & x);

    void from_json(const json & j, ListPromptsRequestProperties & x);
    void to_json(json & j, const ListPromptsRequestProperties & x);

    void from_json(const json & j, ListSRequest & x);
    void to_json(json & j, const ListSRequest & x);

    void from_json(const json & j, ListPromptsResultProperties & x);
    void to_json(json & j, const ListPromptsResultProperties & x);

    void from_json(const json & j, ListPromptsResult & x);
    void to_json(json & j, const ListPromptsResult & x);

    void from_json(const json & j, ListResourceTemplatesResultProperties & x);
    void to_json(json & j, const ListResourceTemplatesResultProperties & x);

    void from_json(const json & j, ListResourceTemplatesResult & x);
    void to_json(json & j, const ListResourceTemplatesResult & x);

    void from_json(const json & j, ListResourcesResultProperties & x);
    void to_json(json & j, const ListResourcesResultProperties & x);

    void from_json(const json & j, ListResourcesResult & x);
    void to_json(json & j, const ListResourcesResult & x);

    void from_json(const json & j, ListRootsRequestProperties & x);
    void to_json(json & j, const ListRootsRequestProperties & x);

    void from_json(const json & j, Request & x);
    void to_json(json & j, const Request & x);

    void from_json(const json & j, ListRootsResultProperties & x);
    void to_json(json & j, const ListRootsResultProperties & x);

    void from_json(const json & j, ListRootsResult & x);
    void to_json(json & j, const ListRootsResult & x);

    void from_json(const json & j, ListToolsResultProperties & x);
    void to_json(json & j, const ListToolsResultProperties & x);

    void from_json(const json & j, ListToolsResult & x);
    void to_json(json & j, const ListToolsResult & x);

    void from_json(const json & j, FriskyProperties & x);
    void to_json(json & j, const FriskyProperties & x);

    void from_json(const json & j, CunningParams & x);
    void to_json(json & j, const CunningParams & x);

    void from_json(const json & j, LoggingMessageNotificationProperties & x);
    void to_json(json & j, const LoggingMessageNotificationProperties & x);

    void from_json(const json & j, LoggingMessageNotification & x);
    void to_json(json & j, const LoggingMessageNotification & x);

    void from_json(const json & j, ModelHintProperties & x);
    void to_json(json & j, const ModelHintProperties & x);

    void from_json(const json & j, ModelHint & x);
    void to_json(json & j, const ModelHint & x);

    void from_json(const json & j, ModelPreferencesProperties & x);
    void to_json(json & j, const ModelPreferencesProperties & x);

    void from_json(const json & j, ModelPreferences & x);
    void to_json(json & j, const ModelPreferences & x);

    void from_json(const json & j, NotificationProperties & x);
    void to_json(json & j, const NotificationProperties & x);

    void from_json(const json & j, Notification & x);
    void to_json(json & j, const Notification & x);

    void from_json(const json & j, PaginatedRequestProperties & x);
    void to_json(json & j, const PaginatedRequestProperties & x);

    void from_json(const json & j, PaginatedRequest & x);
    void to_json(json & j, const PaginatedRequest & x);

    void from_json(const json & j, PaginatedResultProperties & x);
    void to_json(json & j, const PaginatedResultProperties & x);

    void from_json(const json & j, PaginatedResult & x);
    void to_json(json & j, const PaginatedResult & x);

    void from_json(const json & j, MischievousProperties & x);
    void to_json(json & j, const MischievousProperties & x);

    void from_json(const json & j, MagentaParams & x);
    void to_json(json & j, const MagentaParams & x);

    void from_json(const json & j, ProgressNotificationProperties & x);
    void to_json(json & j, const ProgressNotificationProperties & x);

    void from_json(const json & j, ProgressNotification & x);
    void to_json(json & j, const ProgressNotification & x);

    void from_json(const json & j, ProgressToken & x);
    void to_json(json & j, const ProgressToken & x);

    void from_json(const json & j, PromptProperties & x);
    void to_json(json & j, const PromptProperties & x);

    void from_json(const json & j, Prompt & x);
    void to_json(json & j, const Prompt & x);

    void from_json(const json & j, PromptArgumentProperties & x);
    void to_json(json & j, const PromptArgumentProperties & x);

    void from_json(const json & j, PromptArgument & x);
    void to_json(json & j, const PromptArgument & x);

    void from_json(const json & j, PromptMessageProperties & x);
    void to_json(json & j, const PromptMessageProperties & x);

    void from_json(const json & j, Message & x);
    void to_json(json & j, const Message & x);

    void from_json(const json & j, PromptReferenceProperties & x);
    void to_json(json & j, const PromptReferenceProperties & x);

    void from_json(const json & j, PromptReference & x);
    void to_json(json & j, const PromptReference & x);

    void from_json(const json & j, BraggadociousProperties & x);
    void to_json(json & j, const BraggadociousProperties & x);

    void from_json(const json & j, FriskyParams & x);
    void to_json(json & j, const FriskyParams & x);

    void from_json(const json & j, ReadResourceRequestProperties & x);
    void to_json(json & j, const ReadResourceRequestProperties & x);

    void from_json(const json & j, ReadResourceRequest & x);
    void to_json(json & j, const ReadResourceRequest & x);

    void from_json(const json & j, ReadResourceResultProperties & x);
    void to_json(json & j, const ReadResourceResultProperties & x);

    void from_json(const json & j, ReadResourceResult & x);
    void to_json(json & j, const ReadResourceResult & x);

    void from_json(const json & j, RequestProperties & x);
    void to_json(json & j, const RequestProperties & x);

    void from_json(const json & j, RequestClass & x);
    void to_json(json & j, const RequestClass & x);

    void from_json(const json & j, ResourceProperties & x);
    void to_json(json & j, const ResourceProperties & x);

    void from_json(const json & j, Resource & x);
    void to_json(json & j, const Resource & x);

    void from_json(const json & j, ResourceContentsProperties & x);
    void to_json(json & j, const ResourceContentsProperties & x);

    void from_json(const json & j, ResourceContents & x);
    void to_json(json & j, const ResourceContents & x);

    void from_json(const json & j, ResourceReferenceProperties & x);
    void to_json(json & j, const ResourceReferenceProperties & x);

    void from_json(const json & j, ResourceReference & x);
    void to_json(json & j, const ResourceReference & x);

    void from_json(const json & j, ResourceTemplateProperties & x);
    void to_json(json & j, const ResourceTemplateProperties & x);

    void from_json(const json & j, ResourceTemplate & x);
    void to_json(json & j, const ResourceTemplate & x);

    void from_json(const json & j, RootProperties & x);
    void to_json(json & j, const RootProperties & x);

    void from_json(const json & j, Root & x);
    void to_json(json & j, const Root & x);

    void from_json(const json & j, ResourcesProperties & x);
    void to_json(json & j, const ResourcesProperties & x);

    void from_json(const json & j, Resources & x);
    void to_json(json & j, const Resources & x);

    void from_json(const json & j, ServerCapabilitiesProperties & x);
    void to_json(json & j, const ServerCapabilitiesProperties & x);

    void from_json(const json & j, ServerCapabilities & x);
    void to_json(json & j, const ServerCapabilities & x);

    void from_json(const json & j, Properties1 & x);
    void to_json(json & j, const Properties1 & x);

    void from_json(const json & j, MischievousParams & x);
    void to_json(json & j, const MischievousParams & x);

    void from_json(const json & j, SetLevelRequestProperties & x);
    void to_json(json & j, const SetLevelRequestProperties & x);

    void from_json(const json & j, SetLevelRequest & x);
    void to_json(json & j, const SetLevelRequest & x);

    void from_json(const json & j, TextContentProperties & x);
    void to_json(json & j, const TextContentProperties & x);

    void from_json(const json & j, TextContent & x);
    void to_json(json & j, const TextContent & x);

    void from_json(const json & j, TextResourceContentsProperties & x);
    void to_json(json & j, const TextResourceContentsProperties & x);

    void from_json(const json & j, TextResourceContents & x);
    void to_json(json & j, const TextResourceContents & x);

    void from_json(const json & j, PropertiesProperties & x);
    void to_json(json & j, const PropertiesProperties & x);

    void from_json(const json & j, InputSchemaProperties & x);
    void to_json(json & j, const InputSchemaProperties & x);

    void from_json(const json & j, InputSchema & x);
    void to_json(json & j, const InputSchema & x);

    void from_json(const json & j, ToolProperties & x);
    void to_json(json & j, const ToolProperties & x);

    void from_json(const json & j, Tool & x);
    void to_json(json & j, const Tool & x);

    void from_json(const json & j, ToolAnnotationsProperties & x);
    void to_json(json & j, const ToolAnnotationsProperties & x);

    void from_json(const json & j, ToolAnnotations & x);
    void to_json(json & j, const ToolAnnotations & x);

    void from_json(const json & j, Definitions & x);
    void to_json(json & j, const Definitions & x);

    void from_json(const json & j, Schema & x);
    void to_json(json & j, const Schema & x);

    void from_json(const json & j, TypeElement & x);
    void to_json(json & j, const TypeElement & x);

    void from_json(const json & j, AnnotationsType & x);
    void to_json(json & j, const AnnotationsType & x);

    void from_json(const json & j, Required & x);
    void to_json(json & j, const Required & x);

    inline void from_json(const json & j, EmptyResult& x) {
        x.set_ref(j.at("$ref").get<std::string>());
    }

    inline void to_json(json & j, const EmptyResult & x) {
        j = json::object();
        j["$ref"] = x.get_ref();
    }

    inline void from_json(const json & j, Audience& x) {
        x.set_description(j.at("description").get<std::string>());
        x.set_items(j.at("items").get<EmptyResult>());
        x.set_type(j.at("type").get<std::string>());
    }

    inline void to_json(json & j, const Audience & x) {
        j = json::object();
        j["description"] = x.get_description();
        j["items"] = x.get_items();
        j["type"] = x.get_type();
    }

    inline void from_json(const json & j, Priority& x) {
        x.set_description(j.at("description").get<std::string>());
        x.set_maximum(j.at("maximum").get<int64_t>());
        x.set_minimum(j.at("minimum").get<int64_t>());
        x.set_type(j.at("type").get<TypeElement>());
    }

    inline void to_json(json & j, const Priority & x) {
        j = json::object();
        j["description"] = x.get_description();
        j["maximum"] = x.get_maximum();
        j["minimum"] = x.get_minimum();
        j["type"] = x.get_type();
    }

    inline void from_json(const json & j, AnnotationsProperties& x) {
        x.set_audience(j.at("audience").get<Audience>());
        x.set_priority(j.at("priority").get<Priority>());
    }

    inline void to_json(json & j, const AnnotationsProperties & x) {
        j = json::object();
        j["audience"] = x.get_audience();
        j["priority"] = x.get_priority();
    }

    inline void from_json(const json & j, Annotations& x) {
        x.set_description(j.at("description").get<std::string>());
        x.set_properties(j.at("properties").get<AnnotationsProperties>());
        x.set_type(j.at("type").get<AnnotationsType>());
    }

    inline void to_json(json & j, const Annotations & x) {
        j = json::object();
        j["description"] = x.get_description();
        j["properties"] = x.get_properties();
        j["type"] = x.get_type();
    }

    inline void from_json(const json & j, AnnotationsClass& x) {
        x.set_ref(j.at("$ref").get<std::string>());
        x.set_description(j.at("description").get<std::string>());
    }

    inline void to_json(json & j, const AnnotationsClass & x) {
        j = json::object();
        j["$ref"] = x.get_ref();
        j["description"] = x.get_description();
    }

    inline void from_json(const json & j, BlobClass& x) {
        x.set_description(j.at("description").get<std::string>());
        x.set_format(j.at("format").get<Required>());
        x.set_type(j.at("type").get<TypeElement>());
    }

    inline void to_json(json & j, const BlobClass & x) {
        j = json::object();
        j["description"] = x.get_description();
        j["format"] = x.get_format();
        j["type"] = x.get_type();
    }

    inline void from_json(const json & j, Cursor& x) {
        x.set_description(j.at("description").get<std::string>());
        x.set_type(j.at("type").get<TypeElement>());
    }

    inline void to_json(json & j, const Cursor & x) {
        j = json::object();
        j["description"] = x.get_description();
        j["type"] = x.get_type();
    }

    inline void from_json(const json & j, TypeClass& x) {
        x.set_type_const(j.at("const").get<std::string>());
        x.set_type(j.at("type").get<TypeElement>());
    }

    inline void to_json(json & j, const TypeClass & x) {
        j = json::object();
        j["const"] = x.get_type_const();
        j["type"] = x.get_type();
    }

    inline void from_json(const json & j, AudioContentProperties& x) {
        x.set_annotations(j.at("annotations").get<AnnotationsClass>());
        x.set_data(j.at("data").get<BlobClass>());
        x.set_mime_type(j.at("mimeType").get<Cursor>());
        x.set_type(j.at("type").get<TypeClass>());
    }

    inline void to_json(json & j, const AudioContentProperties & x) {
        j = json::object();
        j["annotations"] = x.get_annotations();
        j["data"] = x.get_data();
        j["mimeType"] = x.get_mime_type();
        j["type"] = x.get_type();
    }

    inline void from_json(const json & j, Content& x) {
        x.set_description(j.at("description").get<std::string>());
        x.set_properties(j.at("properties").get<AudioContentProperties>());
        x.set_required(j.at("required").get<std::vector<std::string>>());
        x.set_type(j.at("type").get<AnnotationsType>());
    }

    inline void to_json(json & j, const Content & x) {
        j = json::object();
        j["description"] = x.get_description();
        j["properties"] = x.get_properties();
        j["required"] = x.get_required();
        j["type"] = x.get_type();
    }

    inline void from_json(const json & j, BlobResourceContentsProperties& x) {
        x.set_blob(j.at("blob").get<BlobClass>());
        x.set_mime_type(j.at("mimeType").get<Cursor>());
        x.set_uri(j.at("uri").get<BlobClass>());
    }

    inline void to_json(json & j, const BlobResourceContentsProperties & x) {
        j = json::object();
        j["blob"] = x.get_blob();
        j["mimeType"] = x.get_mime_type();
        j["uri"] = x.get_uri();
    }

    inline void from_json(const json & j, BlobResourceContents& x) {
        x.set_properties(j.at("properties").get<BlobResourceContentsProperties>());
        x.set_required(j.at("required").get<std::vector<std::string>>());
        x.set_type(j.at("type").get<AnnotationsType>());
    }

    inline void to_json(json & j, const BlobResourceContents & x) {
        j = json::object();
        j["properties"] = x.get_properties();
        j["required"] = x.get_required();
        j["type"] = x.get_type();
    }

    inline void from_json(const json & j, AdditionalPropertiesClass& x) {
    }

    inline void to_json(json & j, const AdditionalPropertiesClass & x) {
        j = json::object();
    }

    inline void from_json(const json & j, PurpleArguments& x) {
        x.set_additional_properties(j.at("additionalProperties").get<AdditionalPropertiesClass>());
        x.set_type(j.at("type").get<AnnotationsType>());
    }

    inline void to_json(json & j, const PurpleArguments & x) {
        j = json::object();
        j["additionalProperties"] = x.get_additional_properties();
        j["type"] = x.get_type();
    }

    inline void from_json(const json & j, Name& x) {
        x.set_type(j.at("type").get<TypeElement>());
    }

    inline void to_json(json & j, const Name & x) {
        j = json::object();
        j["type"] = x.get_type();
    }

    inline void from_json(const json & j, PurpleProperties& x) {
        x.set_arguments(j.at("arguments").get<PurpleArguments>());
        x.set_name(j.at("name").get<Name>());
    }

    inline void to_json(json & j, const PurpleProperties & x) {
        j = json::object();
        j["arguments"] = x.get_arguments();
        j["name"] = x.get_name();
    }

    inline void from_json(const json & j, PurpleParams& x) {
        x.set_properties(j.at("properties").get<PurpleProperties>());
        x.set_required(j.at("required").get<std::vector<std::string>>());
        x.set_type(j.at("type").get<AnnotationsType>());
    }

    inline void to_json(json & j, const PurpleParams & x) {
        j = json::object();
        j["properties"] = x.get_properties();
        j["required"] = x.get_required();
        j["type"] = x.get_type();
    }

    inline void from_json(const json & j, CallToolRequestProperties& x) {
        x.set_method(j.at("method").get<TypeClass>());
        x.set_params(j.at("params").get<PurpleParams>());
    }

    inline void to_json(json & j, const CallToolRequestProperties & x) {
        j = json::object();
        j["method"] = x.get_method();
        j["params"] = x.get_params();
    }

    inline void from_json(const json & j, CallToolRequest& x) {
        x.set_description(j.at("description").get<std::string>());
        x.set_properties(j.at("properties").get<CallToolRequestProperties>());
        x.set_required(j.at("required").get<std::vector<std::string>>());
        x.set_type(j.at("type").get<AnnotationsType>());
    }

    inline void to_json(json & j, const CallToolRequest & x) {
        j = json::object();
        j["description"] = x.get_description();
        j["properties"] = x.get_properties();
        j["required"] = x.get_required();
        j["type"] = x.get_type();
    }

    inline void from_json(const json & j, ClientNotification& x) {
        x.set_any_of(j.at("anyOf").get<std::vector<EmptyResult>>());
    }

    inline void to_json(json & j, const ClientNotification & x) {
        j = json::object();
        j["anyOf"] = x.get_any_of();
    }

    inline void from_json(const json & j, ContentClass& x) {
        x.set_items(j.at("items").get<ClientNotification>());
        x.set_type(j.at("type").get<std::string>());
    }

    inline void to_json(json & j, const ContentClass & x) {
        j = json::object();
        j["items"] = x.get_items();
        j["type"] = x.get_type();
    }

    inline void from_json(const json & j, PurpleMeta& x) {
        x.set_additional_properties(j.at("additionalProperties").get<AdditionalPropertiesClass>());
        x.set_description(j.at("description").get<std::string>());
        x.set_type(j.at("type").get<AnnotationsType>());
    }

    inline void to_json(json & j, const PurpleMeta & x) {
        j = json::object();
        j["additionalProperties"] = x.get_additional_properties();
        j["description"] = x.get_description();
        j["type"] = x.get_type();
    }

    inline void from_json(const json & j, CallToolResultProperties& x) {
        x.set_meta(j.at("_meta").get<PurpleMeta>());
        x.set_content(j.at("content").get<ContentClass>());
        x.set_is_error(j.at("isError").get<Cursor>());
    }

    inline void to_json(json & j, const CallToolResultProperties & x) {
        j = json::object();
        j["_meta"] = x.get_meta();
        j["content"] = x.get_content();
        j["isError"] = x.get_is_error();
    }

    inline void from_json(const json & j, CallToolResult& x) {
        x.set_description(j.at("description").get<std::string>());
        x.set_properties(j.at("properties").get<CallToolResultProperties>());
        x.set_required(j.at("required").get<std::vector<std::string>>());
        x.set_type(j.at("type").get<AnnotationsType>());
    }

    inline void to_json(json & j, const CallToolResult & x) {
        j = json::object();
        j["description"] = x.get_description();
        j["properties"] = x.get_properties();
        j["required"] = x.get_required();
        j["type"] = x.get_type();
    }

    inline void from_json(const json & j, FluffyProperties& x) {
        x.set_reason(j.at("reason").get<Cursor>());
        x.set_request_id(j.at("requestId").get<AnnotationsClass>());
    }

    inline void to_json(json & j, const FluffyProperties & x) {
        j = json::object();
        j["reason"] = x.get_reason();
        j["requestId"] = x.get_request_id();
    }

    inline void from_json(const json & j, FluffyParams& x) {
        x.set_properties(j.at("properties").get<FluffyProperties>());
        x.set_required(j.at("required").get<std::vector<std::string>>());
        x.set_type(j.at("type").get<AnnotationsType>());
    }

    inline void to_json(json & j, const FluffyParams & x) {
        j = json::object();
        j["properties"] = x.get_properties();
        j["required"] = x.get_required();
        j["type"] = x.get_type();
    }

    inline void from_json(const json & j, CancelledNotificationProperties& x) {
        x.set_method(j.at("method").get<TypeClass>());
        x.set_params(j.at("params").get<FluffyParams>());
    }

    inline void to_json(json & j, const CancelledNotificationProperties & x) {
        j = json::object();
        j["method"] = x.get_method();
        j["params"] = x.get_params();
    }

    inline void from_json(const json & j, CancelledNotification& x) {
        x.set_description(j.at("description").get<std::string>());
        x.set_properties(j.at("properties").get<CancelledNotificationProperties>());
        x.set_required(j.at("required").get<std::vector<std::string>>());
        x.set_type(j.at("type").get<AnnotationsType>());
    }

    inline void to_json(json & j, const CancelledNotification & x) {
        j = json::object();
        j["description"] = x.get_description();
        j["properties"] = x.get_properties();
        j["required"] = x.get_required();
        j["type"] = x.get_type();
    }

    inline void from_json(const json & j, Sampling& x) {
        x.set_additional_properties(j.at("additionalProperties").get<bool>());
        x.set_properties(j.at("properties").get<AdditionalPropertiesClass>());
        x.set_type(j.at("type").get<AnnotationsType>());
        x.set_description(get_stack_optional<std::string>(j, "description"));
    }

    inline void to_json(json & j, const Sampling & x) {
        j = json::object();
        j["additionalProperties"] = x.get_additional_properties();
        j["properties"] = x.get_properties();
        j["type"] = x.get_type();
        j["description"] = x.get_description();
    }

    inline void from_json(const json & j, Experimental& x) {
        x.set_additional_properties(j.at("additionalProperties").get<Sampling>());
        x.set_description(j.at("description").get<std::string>());
        x.set_type(j.at("type").get<AnnotationsType>());
    }

    inline void to_json(json & j, const Experimental & x) {
        j = json::object();
        j["additionalProperties"] = x.get_additional_properties();
        j["description"] = x.get_description();
        j["type"] = x.get_type();
    }

    inline void from_json(const json & j, RootsProperties& x) {
        x.set_list_changed(j.at("listChanged").get<Cursor>());
    }

    inline void to_json(json & j, const RootsProperties & x) {
        j = json::object();
        j["listChanged"] = x.get_list_changed();
    }

    inline void from_json(const json & j, Roots& x) {
        x.set_description(j.at("description").get<std::string>());
        x.set_properties(j.at("properties").get<RootsProperties>());
        x.set_type(j.at("type").get<AnnotationsType>());
    }

    inline void to_json(json & j, const Roots & x) {
        j = json::object();
        j["description"] = x.get_description();
        j["properties"] = x.get_properties();
        j["type"] = x.get_type();
    }

    inline void from_json(const json & j, ClientCapabilitiesProperties& x) {
        x.set_experimental(j.at("experimental").get<Experimental>());
        x.set_roots(j.at("roots").get<Roots>());
        x.set_sampling(j.at("sampling").get<Sampling>());
    }

    inline void to_json(json & j, const ClientCapabilitiesProperties & x) {
        j = json::object();
        j["experimental"] = x.get_experimental();
        j["roots"] = x.get_roots();
        j["sampling"] = x.get_sampling();
    }

    inline void from_json(const json & j, ClientCapabilities& x) {
        x.set_description(j.at("description").get<std::string>());
        x.set_properties(j.at("properties").get<ClientCapabilitiesProperties>());
        x.set_type(j.at("type").get<AnnotationsType>());
    }

    inline void to_json(json & j, const ClientCapabilities & x) {
        j = json::object();
        j["description"] = x.get_description();
        j["properties"] = x.get_properties();
        j["type"] = x.get_type();
    }

    inline void from_json(const json & j, ArgumentProperties& x) {
        x.set_name(j.at("name").get<Cursor>());
        x.set_value(j.at("value").get<Cursor>());
    }

    inline void to_json(json & j, const ArgumentProperties & x) {
        j = json::object();
        j["name"] = x.get_name();
        j["value"] = x.get_value();
    }

    inline void from_json(const json & j, Argument& x) {
        x.set_description(j.at("description").get<std::string>());
        x.set_properties(j.at("properties").get<ArgumentProperties>());
        x.set_required(j.at("required").get<std::vector<std::string>>());
        x.set_type(j.at("type").get<AnnotationsType>());
    }

    inline void to_json(json & j, const Argument & x) {
        j = json::object();
        j["description"] = x.get_description();
        j["properties"] = x.get_properties();
        j["required"] = x.get_required();
        j["type"] = x.get_type();
    }

    inline void from_json(const json & j, TentacledProperties& x) {
        x.set_argument(j.at("argument").get<Argument>());
        x.set_ref(j.at("ref").get<ClientNotification>());
    }

    inline void to_json(json & j, const TentacledProperties & x) {
        j = json::object();
        j["argument"] = x.get_argument();
        j["ref"] = x.get_ref();
    }

    inline void from_json(const json & j, TentacledParams& x) {
        x.set_properties(j.at("properties").get<TentacledProperties>());
        x.set_required(j.at("required").get<std::vector<std::string>>());
        x.set_type(j.at("type").get<AnnotationsType>());
    }

    inline void to_json(json & j, const TentacledParams & x) {
        j = json::object();
        j["properties"] = x.get_properties();
        j["required"] = x.get_required();
        j["type"] = x.get_type();
    }

    inline void from_json(const json & j, CompleteRequestProperties& x) {
        x.set_method(j.at("method").get<TypeClass>());
        x.set_params(j.at("params").get<TentacledParams>());
    }

    inline void to_json(json & j, const CompleteRequestProperties & x) {
        j = json::object();
        j["method"] = x.get_method();
        j["params"] = x.get_params();
    }

    inline void from_json(const json & j, CompleteRequest& x) {
        x.set_description(j.at("description").get<std::string>());
        x.set_properties(j.at("properties").get<CompleteRequestProperties>());
        x.set_required(j.at("required").get<std::vector<std::string>>());
        x.set_type(j.at("type").get<AnnotationsType>());
    }

    inline void to_json(json & j, const CompleteRequest & x) {
        j = json::object();
        j["description"] = x.get_description();
        j["properties"] = x.get_properties();
        j["required"] = x.get_required();
        j["type"] = x.get_type();
    }

    inline void from_json(const json & j, Values& x) {
        x.set_description(j.at("description").get<std::string>());
        x.set_items(j.at("items").get<Name>());
        x.set_type(j.at("type").get<std::string>());
    }

    inline void to_json(json & j, const Values & x) {
        j = json::object();
        j["description"] = x.get_description();
        j["items"] = x.get_items();
        j["type"] = x.get_type();
    }

    inline void from_json(const json & j, CompletionProperties& x) {
        x.set_has_more(j.at("hasMore").get<Cursor>());
        x.set_total(j.at("total").get<Cursor>());
        x.set_values(j.at("values").get<Values>());
    }

    inline void to_json(json & j, const CompletionProperties & x) {
        j = json::object();
        j["hasMore"] = x.get_has_more();
        j["total"] = x.get_total();
        j["values"] = x.get_values();
    }

    inline void from_json(const json & j, Completion& x) {
        x.set_properties(j.at("properties").get<CompletionProperties>());
        x.set_required(j.at("required").get<std::vector<std::string>>());
        x.set_type(j.at("type").get<AnnotationsType>());
    }

    inline void to_json(json & j, const Completion & x) {
        j = json::object();
        j["properties"] = x.get_properties();
        j["required"] = x.get_required();
        j["type"] = x.get_type();
    }

    inline void from_json(const json & j, CompleteResultProperties& x) {
        x.set_meta(j.at("_meta").get<PurpleMeta>());
        x.set_completion(j.at("completion").get<Completion>());
    }

    inline void to_json(json & j, const CompleteResultProperties & x) {
        j = json::object();
        j["_meta"] = x.get_meta();
        j["completion"] = x.get_completion();
    }

    inline void from_json(const json & j, CompleteResult& x) {
        x.set_description(j.at("description").get<std::string>());
        x.set_properties(j.at("properties").get<CompleteResultProperties>());
        x.set_required(j.at("required").get<std::vector<std::string>>());
        x.set_type(j.at("type").get<AnnotationsType>());
    }

    inline void to_json(json & j, const CompleteResult & x) {
        j = json::object();
        j["description"] = x.get_description();
        j["properties"] = x.get_properties();
        j["required"] = x.get_required();
        j["type"] = x.get_type();
    }

    inline void from_json(const json & j, LoggingLevel& x) {
        x.set_description(j.at("description").get<std::string>());
        x.set_logging_level_enum(j.at("enum").get<std::vector<std::string>>());
        x.set_type(j.at("type").get<TypeElement>());
    }

    inline void to_json(json & j, const LoggingLevel & x) {
        j = json::object();
        j["description"] = x.get_description();
        j["enum"] = x.get_logging_level_enum();
        j["type"] = x.get_type();
    }

    inline void from_json(const json & j, Messages& x) {
        x.set_items(j.at("items").get<EmptyResult>());
        x.set_type(j.at("type").get<std::string>());
    }

    inline void to_json(json & j, const Messages & x) {
        j = json::object();
        j["items"] = x.get_items();
        j["type"] = x.get_type();
    }

    inline void from_json(const json & j, StopSequences& x) {
        x.set_items(j.at("items").get<Name>());
        x.set_type(j.at("type").get<std::string>());
    }

    inline void to_json(json & j, const StopSequences & x) {
        j = json::object();
        j["items"] = x.get_items();
        j["type"] = x.get_type();
    }

    inline void from_json(const json & j, StickyProperties& x) {
        x.set_include_context(j.at("includeContext").get<LoggingLevel>());
        x.set_max_tokens(j.at("maxTokens").get<Cursor>());
        x.set_messages(j.at("messages").get<Messages>());
        x.set_metadata(j.at("metadata").get<Sampling>());
        x.set_model_preferences(j.at("modelPreferences").get<AnnotationsClass>());
        x.set_stop_sequences(j.at("stopSequences").get<StopSequences>());
        x.set_system_prompt(j.at("systemPrompt").get<Cursor>());
        x.set_temperature(j.at("temperature").get<Name>());
    }

    inline void to_json(json & j, const StickyProperties & x) {
        j = json::object();
        j["includeContext"] = x.get_include_context();
        j["maxTokens"] = x.get_max_tokens();
        j["messages"] = x.get_messages();
        j["metadata"] = x.get_metadata();
        j["modelPreferences"] = x.get_model_preferences();
        j["stopSequences"] = x.get_stop_sequences();
        j["systemPrompt"] = x.get_system_prompt();
        j["temperature"] = x.get_temperature();
    }

    inline void from_json(const json & j, StickyParams& x) {
        x.set_properties(j.at("properties").get<StickyProperties>());
        x.set_required(j.at("required").get<std::vector<std::string>>());
        x.set_type(j.at("type").get<AnnotationsType>());
    }

    inline void to_json(json & j, const StickyParams & x) {
        j = json::object();
        j["properties"] = x.get_properties();
        j["required"] = x.get_required();
        j["type"] = x.get_type();
    }

    inline void from_json(const json & j, CreateMessageRequestProperties& x) {
        x.set_method(j.at("method").get<TypeClass>());
        x.set_params(j.at("params").get<StickyParams>());
    }

    inline void to_json(json & j, const CreateMessageRequestProperties & x) {
        j = json::object();
        j["method"] = x.get_method();
        j["params"] = x.get_params();
    }

    inline void from_json(const json & j, CreateMessageRequest& x) {
        x.set_description(j.at("description").get<std::string>());
        x.set_properties(j.at("properties").get<CreateMessageRequestProperties>());
        x.set_required(j.at("required").get<std::vector<std::string>>());
        x.set_type(j.at("type").get<AnnotationsType>());
    }

    inline void to_json(json & j, const CreateMessageRequest & x) {
        j = json::object();
        j["description"] = x.get_description();
        j["properties"] = x.get_properties();
        j["required"] = x.get_required();
        j["type"] = x.get_type();
    }

    inline void from_json(const json & j, CreateMessageResultProperties& x) {
        x.set_meta(j.at("_meta").get<PurpleMeta>());
        x.set_content(j.at("content").get<ClientNotification>());
        x.set_model(j.at("model").get<Cursor>());
        x.set_role(j.at("role").get<EmptyResult>());
        x.set_stop_reason(j.at("stopReason").get<Cursor>());
    }

    inline void to_json(json & j, const CreateMessageResultProperties & x) {
        j = json::object();
        j["_meta"] = x.get_meta();
        j["content"] = x.get_content();
        j["model"] = x.get_model();
        j["role"] = x.get_role();
        j["stopReason"] = x.get_stop_reason();
    }

    inline void from_json(const json & j, CreateMessageResult& x) {
        x.set_description(j.at("description").get<std::string>());
        x.set_properties(j.at("properties").get<CreateMessageResultProperties>());
        x.set_required(j.at("required").get<std::vector<std::string>>());
        x.set_type(j.at("type").get<AnnotationsType>());
    }

    inline void to_json(json & j, const CreateMessageResult & x) {
        j = json::object();
        j["description"] = x.get_description();
        j["properties"] = x.get_properties();
        j["required"] = x.get_required();
        j["type"] = x.get_type();
    }

    inline void from_json(const json & j, EmbeddedResourceProperties& x) {
        x.set_annotations(j.at("annotations").get<AnnotationsClass>());
        x.set_resource(j.at("resource").get<ClientNotification>());
        x.set_type(j.at("type").get<TypeClass>());
    }

    inline void to_json(json & j, const EmbeddedResourceProperties & x) {
        j = json::object();
        j["annotations"] = x.get_annotations();
        j["resource"] = x.get_resource();
        j["type"] = x.get_type();
    }

    inline void from_json(const json & j, EmbeddedResource& x) {
        x.set_description(j.at("description").get<std::string>());
        x.set_properties(j.at("properties").get<EmbeddedResourceProperties>());
        x.set_required(j.at("required").get<std::vector<std::string>>());
        x.set_type(j.at("type").get<AnnotationsType>());
    }

    inline void to_json(json & j, const EmbeddedResource & x) {
        j = json::object();
        j["description"] = x.get_description();
        j["properties"] = x.get_properties();
        j["required"] = x.get_required();
        j["type"] = x.get_type();
    }

    inline void from_json(const json & j, FluffyArguments& x) {
        x.set_additional_properties(j.at("additionalProperties").get<Name>());
        x.set_description(j.at("description").get<std::string>());
        x.set_type(j.at("type").get<AnnotationsType>());
    }

    inline void to_json(json & j, const FluffyArguments & x) {
        j = json::object();
        j["additionalProperties"] = x.get_additional_properties();
        j["description"] = x.get_description();
        j["type"] = x.get_type();
    }

    inline void from_json(const json & j, IndigoProperties& x) {
        x.set_arguments(j.at("arguments").get<FluffyArguments>());
        x.set_name(j.at("name").get<Cursor>());
    }

    inline void to_json(json & j, const IndigoProperties & x) {
        j = json::object();
        j["arguments"] = x.get_arguments();
        j["name"] = x.get_name();
    }

    inline void from_json(const json & j, IndigoParams& x) {
        x.set_properties(j.at("properties").get<IndigoProperties>());
        x.set_required(j.at("required").get<std::vector<std::string>>());
        x.set_type(j.at("type").get<AnnotationsType>());
    }

    inline void to_json(json & j, const IndigoParams & x) {
        j = json::object();
        j["properties"] = x.get_properties();
        j["required"] = x.get_required();
        j["type"] = x.get_type();
    }

    inline void from_json(const json & j, GetPromptRequestProperties& x) {
        x.set_method(j.at("method").get<TypeClass>());
        x.set_params(j.at("params").get<IndigoParams>());
    }

    inline void to_json(json & j, const GetPromptRequestProperties & x) {
        j = json::object();
        j["method"] = x.get_method();
        j["params"] = x.get_params();
    }

    inline void from_json(const json & j, GetPromptRequest& x) {
        x.set_description(j.at("description").get<std::string>());
        x.set_properties(j.at("properties").get<GetPromptRequestProperties>());
        x.set_required(j.at("required").get<std::vector<std::string>>());
        x.set_type(j.at("type").get<AnnotationsType>());
    }

    inline void to_json(json & j, const GetPromptRequest & x) {
        j = json::object();
        j["description"] = x.get_description();
        j["properties"] = x.get_properties();
        j["required"] = x.get_required();
        j["type"] = x.get_type();
    }

    inline void from_json(const json & j, GetPromptResultProperties& x) {
        x.set_meta(j.at("_meta").get<PurpleMeta>());
        x.set_description(j.at("description").get<Cursor>());
        x.set_messages(j.at("messages").get<Messages>());
    }

    inline void to_json(json & j, const GetPromptResultProperties & x) {
        j = json::object();
        j["_meta"] = x.get_meta();
        j["description"] = x.get_description();
        j["messages"] = x.get_messages();
    }

    inline void from_json(const json & j, GetPromptResult& x) {
        x.set_description(j.at("description").get<std::string>());
        x.set_properties(j.at("properties").get<GetPromptResultProperties>());
        x.set_required(j.at("required").get<std::vector<std::string>>());
        x.set_type(j.at("type").get<AnnotationsType>());
    }

    inline void to_json(json & j, const GetPromptResult & x) {
        j = json::object();
        j["description"] = x.get_description();
        j["properties"] = x.get_properties();
        j["required"] = x.get_required();
        j["type"] = x.get_type();
    }

    inline void from_json(const json & j, ImplementationProperties& x) {
        x.set_name(j.at("name").get<Name>());
        x.set_version(j.at("version").get<Name>());
    }

    inline void to_json(json & j, const ImplementationProperties & x) {
        j = json::object();
        j["name"] = x.get_name();
        j["version"] = x.get_version();
    }

    inline void from_json(const json & j, Implementation& x) {
        x.set_description(j.at("description").get<std::string>());
        x.set_properties(j.at("properties").get<ImplementationProperties>());
        x.set_required(j.at("required").get<std::vector<std::string>>());
        x.set_type(j.at("type").get<AnnotationsType>());
    }

    inline void to_json(json & j, const Implementation & x) {
        j = json::object();
        j["description"] = x.get_description();
        j["properties"] = x.get_properties();
        j["required"] = x.get_required();
        j["type"] = x.get_type();
    }

    inline void from_json(const json & j, IndecentProperties& x) {
        x.set_capabilities(j.at("capabilities").get<EmptyResult>());
        x.set_client_info(j.at("clientInfo").get<EmptyResult>());
        x.set_protocol_version(j.at("protocolVersion").get<Cursor>());
    }

    inline void to_json(json & j, const IndecentProperties & x) {
        j = json::object();
        j["capabilities"] = x.get_capabilities();
        j["clientInfo"] = x.get_client_info();
        j["protocolVersion"] = x.get_protocol_version();
    }

    inline void from_json(const json & j, IndecentParams& x) {
        x.set_properties(j.at("properties").get<IndecentProperties>());
        x.set_required(j.at("required").get<std::vector<std::string>>());
        x.set_type(j.at("type").get<AnnotationsType>());
    }

    inline void to_json(json & j, const IndecentParams & x) {
        j = json::object();
        j["properties"] = x.get_properties();
        j["required"] = x.get_required();
        j["type"] = x.get_type();
    }

    inline void from_json(const json & j, InitializeRequestProperties& x) {
        x.set_method(j.at("method").get<TypeClass>());
        x.set_params(j.at("params").get<IndecentParams>());
    }

    inline void to_json(json & j, const InitializeRequestProperties & x) {
        j = json::object();
        j["method"] = x.get_method();
        j["params"] = x.get_params();
    }

    inline void from_json(const json & j, InitializeRequest& x) {
        x.set_description(j.at("description").get<std::string>());
        x.set_properties(j.at("properties").get<InitializeRequestProperties>());
        x.set_required(j.at("required").get<std::vector<std::string>>());
        x.set_type(j.at("type").get<AnnotationsType>());
    }

    inline void to_json(json & j, const InitializeRequest & x) {
        j = json::object();
        j["description"] = x.get_description();
        j["properties"] = x.get_properties();
        j["required"] = x.get_required();
        j["type"] = x.get_type();
    }

    inline void from_json(const json & j, InitializeResultProperties& x) {
        x.set_meta(j.at("_meta").get<PurpleMeta>());
        x.set_capabilities(j.at("capabilities").get<EmptyResult>());
        x.set_instructions(j.at("instructions").get<Cursor>());
        x.set_protocol_version(j.at("protocolVersion").get<Cursor>());
        x.set_server_info(j.at("serverInfo").get<EmptyResult>());
    }

    inline void to_json(json & j, const InitializeResultProperties & x) {
        j = json::object();
        j["_meta"] = x.get_meta();
        j["capabilities"] = x.get_capabilities();
        j["instructions"] = x.get_instructions();
        j["protocolVersion"] = x.get_protocol_version();
        j["serverInfo"] = x.get_server_info();
    }

    inline void from_json(const json & j, InitializeResult& x) {
        x.set_description(j.at("description").get<std::string>());
        x.set_properties(j.at("properties").get<InitializeResultProperties>());
        x.set_required(j.at("required").get<std::vector<std::string>>());
        x.set_type(j.at("type").get<AnnotationsType>());
    }

    inline void to_json(json & j, const InitializeResult & x) {
        j = json::object();
        j["description"] = x.get_description();
        j["properties"] = x.get_properties();
        j["required"] = x.get_required();
        j["type"] = x.get_type();
    }

    inline void from_json(const json & j, HilariousProperties& x) {
        x.set_meta(j.at("_meta").get<PurpleMeta>());
    }

    inline void to_json(json & j, const HilariousProperties & x) {
        j = json::object();
        j["_meta"] = x.get_meta();
    }

    inline void from_json(const json & j, Result& x) {
        x.set_additional_properties(j.at("additionalProperties").get<AdditionalPropertiesClass>());
        x.set_properties(j.at("properties").get<HilariousProperties>());
        x.set_type(j.at("type").get<AnnotationsType>());
    }

    inline void to_json(json & j, const Result & x) {
        j = json::object();
        j["additionalProperties"] = x.get_additional_properties();
        j["properties"] = x.get_properties();
        j["type"] = x.get_type();
    }

    inline void from_json(const json & j, InitializedNotificationProperties& x) {
        x.set_method(j.at("method").get<TypeClass>());
        x.set_params(j.at("params").get<Result>());
    }

    inline void to_json(json & j, const InitializedNotificationProperties & x) {
        j = json::object();
        j["method"] = x.get_method();
        j["params"] = x.get_params();
    }

    inline void from_json(const json & j, EdNotification& x) {
        x.set_description(j.at("description").get<std::string>());
        x.set_properties(j.at("properties").get<InitializedNotificationProperties>());
        x.set_required(j.at("required").get<std::vector<std::string>>());
        x.set_type(j.at("type").get<AnnotationsType>());
    }

    inline void to_json(json & j, const EdNotification & x) {
        j = json::object();
        j["description"] = x.get_description();
        j["properties"] = x.get_properties();
        j["required"] = x.get_required();
        j["type"] = x.get_type();
    }

    inline void from_json(const json & j, JsonrpcBatchRequest& x) {
        x.set_description(get_stack_optional<std::string>(j, "description"));
        x.set_items(get_stack_optional<ClientNotification>(j, "items"));
        x.set_type(get_stack_optional<std::string>(j, "type"));
        x.set_ref(get_stack_optional<std::string>(j, "$ref"));
    }

    inline void to_json(json & j, const JsonrpcBatchRequest & x) {
        j = json::object();
        j["description"] = x.get_description();
        j["items"] = x.get_items();
        j["type"] = x.get_type();
        j["$ref"] = x.get_ref();
    }

    inline void from_json(const json & j, PurpleData& x) {
        x.set_description(j.at("description").get<std::string>());
    }

    inline void to_json(json & j, const PurpleData & x) {
        j = json::object();
        j["description"] = x.get_description();
    }

    inline void from_json(const json & j, ErrorProperties& x) {
        x.set_code(j.at("code").get<Cursor>());
        x.set_data(j.at("data").get<PurpleData>());
        x.set_message(j.at("message").get<Cursor>());
    }

    inline void to_json(json & j, const ErrorProperties & x) {
        j = json::object();
        j["code"] = x.get_code();
        j["data"] = x.get_data();
        j["message"] = x.get_message();
    }

    inline void from_json(const json & j, Error& x) {
        x.set_properties(j.at("properties").get<ErrorProperties>());
        x.set_required(j.at("required").get<std::vector<std::string>>());
        x.set_type(j.at("type").get<AnnotationsType>());
    }

    inline void to_json(json & j, const Error & x) {
        j = json::object();
        j["properties"] = x.get_properties();
        j["required"] = x.get_required();
        j["type"] = x.get_type();
    }

    inline void from_json(const json & j, JsonrpcErrorProperties& x) {
        x.set_error(j.at("error").get<Error>());
        x.set_id(j.at("id").get<EmptyResult>());
        x.set_jsonrpc(j.at("jsonrpc").get<TypeClass>());
    }

    inline void to_json(json & j, const JsonrpcErrorProperties & x) {
        j = json::object();
        j["error"] = x.get_error();
        j["id"] = x.get_id();
        j["jsonrpc"] = x.get_jsonrpc();
    }

    inline void from_json(const json & j, JsonrpcError& x) {
        x.set_description(j.at("description").get<std::string>());
        x.set_properties(j.at("properties").get<JsonrpcErrorProperties>());
        x.set_required(j.at("required").get<std::vector<std::string>>());
        x.set_type(j.at("type").get<AnnotationsType>());
    }

    inline void to_json(json & j, const JsonrpcError & x) {
        j = json::object();
        j["description"] = x.get_description();
        j["properties"] = x.get_properties();
        j["required"] = x.get_required();
        j["type"] = x.get_type();
    }

    inline void from_json(const json & j, JsonrpcMessage& x) {
        x.set_any_of(j.at("anyOf").get<std::vector<JsonrpcBatchRequest>>());
        x.set_description(j.at("description").get<std::string>());
    }

    inline void to_json(json & j, const JsonrpcMessage & x) {
        j = json::object();
        j["anyOf"] = x.get_any_of();
        j["description"] = x.get_description();
    }

    inline void from_json(const json & j, JsonrpcNotificationProperties& x) {
        x.set_jsonrpc(j.at("jsonrpc").get<TypeClass>());
        x.set_method(j.at("method").get<Name>());
        x.set_params(j.at("params").get<Result>());
    }

    inline void to_json(json & j, const JsonrpcNotificationProperties & x) {
        j = json::object();
        j["jsonrpc"] = x.get_jsonrpc();
        j["method"] = x.get_method();
        j["params"] = x.get_params();
    }

    inline void from_json(const json & j, JsonrpcNotification& x) {
        x.set_description(j.at("description").get<std::string>());
        x.set_properties(j.at("properties").get<JsonrpcNotificationProperties>());
        x.set_required(j.at("required").get<std::vector<std::string>>());
        x.set_type(j.at("type").get<AnnotationsType>());
    }

    inline void to_json(json & j, const JsonrpcNotification & x) {
        j = json::object();
        j["description"] = x.get_description();
        j["properties"] = x.get_properties();
        j["required"] = x.get_required();
        j["type"] = x.get_type();
    }

    inline void from_json(const json & j, CunningProperties& x) {
        x.set_progress_token(j.at("progressToken").get<AnnotationsClass>());
    }

    inline void to_json(json & j, const CunningProperties & x) {
        j = json::object();
        j["progressToken"] = x.get_progress_token();
    }

    inline void from_json(const json & j, FluffyMeta& x) {
        x.set_properties(j.at("properties").get<CunningProperties>());
        x.set_type(j.at("type").get<AnnotationsType>());
    }

    inline void to_json(json & j, const FluffyMeta & x) {
        j = json::object();
        j["properties"] = x.get_properties();
        j["type"] = x.get_type();
    }

    inline void from_json(const json & j, AmbitiousProperties& x) {
        x.set_meta(j.at("_meta").get<FluffyMeta>());
    }

    inline void to_json(json & j, const AmbitiousProperties & x) {
        j = json::object();
        j["_meta"] = x.get_meta();
    }

    inline void from_json(const json & j, HilariousParams& x) {
        x.set_additional_properties(j.at("additionalProperties").get<AdditionalPropertiesClass>());
        x.set_properties(j.at("properties").get<AmbitiousProperties>());
        x.set_type(j.at("type").get<AnnotationsType>());
    }

    inline void to_json(json & j, const HilariousParams & x) {
        j = json::object();
        j["additionalProperties"] = x.get_additional_properties();
        j["properties"] = x.get_properties();
        j["type"] = x.get_type();
    }

    inline void from_json(const json & j, JsonrpcRequestProperties& x) {
        x.set_id(j.at("id").get<EmptyResult>());
        x.set_jsonrpc(j.at("jsonrpc").get<TypeClass>());
        x.set_method(j.at("method").get<Name>());
        x.set_params(j.at("params").get<HilariousParams>());
    }

    inline void to_json(json & j, const JsonrpcRequestProperties & x) {
        j = json::object();
        j["id"] = x.get_id();
        j["jsonrpc"] = x.get_jsonrpc();
        j["method"] = x.get_method();
        j["params"] = x.get_params();
    }

    inline void from_json(const json & j, JsonrpcRequest& x) {
        x.set_description(j.at("description").get<std::string>());
        x.set_properties(j.at("properties").get<JsonrpcRequestProperties>());
        x.set_required(j.at("required").get<std::vector<std::string>>());
        x.set_type(j.at("type").get<AnnotationsType>());
    }

    inline void to_json(json & j, const JsonrpcRequest & x) {
        j = json::object();
        j["description"] = x.get_description();
        j["properties"] = x.get_properties();
        j["required"] = x.get_required();
        j["type"] = x.get_type();
    }

    inline void from_json(const json & j, JsonrpcResponseProperties& x) {
        x.set_id(j.at("id").get<EmptyResult>());
        x.set_jsonrpc(j.at("jsonrpc").get<TypeClass>());
        x.set_result(j.at("result").get<EmptyResult>());
    }

    inline void to_json(json & j, const JsonrpcResponseProperties & x) {
        j = json::object();
        j["id"] = x.get_id();
        j["jsonrpc"] = x.get_jsonrpc();
        j["result"] = x.get_result();
    }

    inline void from_json(const json & j, JsonrpcResponse& x) {
        x.set_description(j.at("description").get<std::string>());
        x.set_properties(j.at("properties").get<JsonrpcResponseProperties>());
        x.set_required(j.at("required").get<std::vector<std::string>>());
        x.set_type(j.at("type").get<AnnotationsType>());
    }

    inline void to_json(json & j, const JsonrpcResponse & x) {
        j = json::object();
        j["description"] = x.get_description();
        j["properties"] = x.get_properties();
        j["required"] = x.get_required();
        j["type"] = x.get_type();
    }

    inline void from_json(const json & j, MagentaProperties& x) {
        x.set_cursor(j.at("cursor").get<Cursor>());
    }

    inline void to_json(json & j, const MagentaProperties & x) {
        j = json::object();
        j["cursor"] = x.get_cursor();
    }

    inline void from_json(const json & j, AmbitiousParams& x) {
        x.set_properties(j.at("properties").get<MagentaProperties>());
        x.set_type(j.at("type").get<AnnotationsType>());
    }

    inline void to_json(json & j, const AmbitiousParams & x) {
        j = json::object();
        j["properties"] = x.get_properties();
        j["type"] = x.get_type();
    }

    inline void from_json(const json & j, ListPromptsRequestProperties& x) {
        x.set_method(j.at("method").get<TypeClass>());
        x.set_params(j.at("params").get<AmbitiousParams>());
    }

    inline void to_json(json & j, const ListPromptsRequestProperties & x) {
        j = json::object();
        j["method"] = x.get_method();
        j["params"] = x.get_params();
    }

    inline void from_json(const json & j, ListSRequest& x) {
        x.set_description(j.at("description").get<std::string>());
        x.set_properties(j.at("properties").get<ListPromptsRequestProperties>());
        x.set_required(j.at("required").get<std::vector<std::string>>());
        x.set_type(j.at("type").get<AnnotationsType>());
    }

    inline void to_json(json & j, const ListSRequest & x) {
        j = json::object();
        j["description"] = x.get_description();
        j["properties"] = x.get_properties();
        j["required"] = x.get_required();
        j["type"] = x.get_type();
    }

    inline void from_json(const json & j, ListPromptsResultProperties& x) {
        x.set_meta(j.at("_meta").get<PurpleMeta>());
        x.set_next_cursor(j.at("nextCursor").get<Cursor>());
        x.set_prompts(j.at("prompts").get<Messages>());
    }

    inline void to_json(json & j, const ListPromptsResultProperties & x) {
        j = json::object();
        j["_meta"] = x.get_meta();
        j["nextCursor"] = x.get_next_cursor();
        j["prompts"] = x.get_prompts();
    }

    inline void from_json(const json & j, ListPromptsResult& x) {
        x.set_description(j.at("description").get<std::string>());
        x.set_properties(j.at("properties").get<ListPromptsResultProperties>());
        x.set_required(j.at("required").get<std::vector<std::string>>());
        x.set_type(j.at("type").get<AnnotationsType>());
    }

    inline void to_json(json & j, const ListPromptsResult & x) {
        j = json::object();
        j["description"] = x.get_description();
        j["properties"] = x.get_properties();
        j["required"] = x.get_required();
        j["type"] = x.get_type();
    }

    inline void from_json(const json & j, ListResourceTemplatesResultProperties& x) {
        x.set_meta(j.at("_meta").get<PurpleMeta>());
        x.set_next_cursor(j.at("nextCursor").get<Cursor>());
        x.set_resource_templates(j.at("resourceTemplates").get<Messages>());
    }

    inline void to_json(json & j, const ListResourceTemplatesResultProperties & x) {
        j = json::object();
        j["_meta"] = x.get_meta();
        j["nextCursor"] = x.get_next_cursor();
        j["resourceTemplates"] = x.get_resource_templates();
    }

    inline void from_json(const json & j, ListResourceTemplatesResult& x) {
        x.set_description(j.at("description").get<std::string>());
        x.set_properties(j.at("properties").get<ListResourceTemplatesResultProperties>());
        x.set_required(j.at("required").get<std::vector<std::string>>());
        x.set_type(j.at("type").get<AnnotationsType>());
    }

    inline void to_json(json & j, const ListResourceTemplatesResult & x) {
        j = json::object();
        j["description"] = x.get_description();
        j["properties"] = x.get_properties();
        j["required"] = x.get_required();
        j["type"] = x.get_type();
    }

    inline void from_json(const json & j, ListResourcesResultProperties& x) {
        x.set_meta(j.at("_meta").get<PurpleMeta>());
        x.set_next_cursor(j.at("nextCursor").get<Cursor>());
        x.set_resources(j.at("resources").get<Messages>());
    }

    inline void to_json(json & j, const ListResourcesResultProperties & x) {
        j = json::object();
        j["_meta"] = x.get_meta();
        j["nextCursor"] = x.get_next_cursor();
        j["resources"] = x.get_resources();
    }

    inline void from_json(const json & j, ListResourcesResult& x) {
        x.set_description(j.at("description").get<std::string>());
        x.set_properties(j.at("properties").get<ListResourcesResultProperties>());
        x.set_required(j.at("required").get<std::vector<std::string>>());
        x.set_type(j.at("type").get<AnnotationsType>());
    }

    inline void to_json(json & j, const ListResourcesResult & x) {
        j = json::object();
        j["description"] = x.get_description();
        j["properties"] = x.get_properties();
        j["required"] = x.get_required();
        j["type"] = x.get_type();
    }

    inline void from_json(const json & j, ListRootsRequestProperties& x) {
        x.set_method(j.at("method").get<TypeClass>());
        x.set_params(j.at("params").get<HilariousParams>());
    }

    inline void to_json(json & j, const ListRootsRequestProperties & x) {
        j = json::object();
        j["method"] = x.get_method();
        j["params"] = x.get_params();
    }

    inline void from_json(const json & j, Request& x) {
        x.set_description(j.at("description").get<std::string>());
        x.set_properties(j.at("properties").get<ListRootsRequestProperties>());
        x.set_required(j.at("required").get<std::vector<std::string>>());
        x.set_type(j.at("type").get<AnnotationsType>());
    }

    inline void to_json(json & j, const Request & x) {
        j = json::object();
        j["description"] = x.get_description();
        j["properties"] = x.get_properties();
        j["required"] = x.get_required();
        j["type"] = x.get_type();
    }

    inline void from_json(const json & j, ListRootsResultProperties& x) {
        x.set_meta(j.at("_meta").get<PurpleMeta>());
        x.set_roots(j.at("roots").get<Messages>());
    }

    inline void to_json(json & j, const ListRootsResultProperties & x) {
        j = json::object();
        j["_meta"] = x.get_meta();
        j["roots"] = x.get_roots();
    }

    inline void from_json(const json & j, ListRootsResult& x) {
        x.set_description(j.at("description").get<std::string>());
        x.set_properties(j.at("properties").get<ListRootsResultProperties>());
        x.set_required(j.at("required").get<std::vector<std::string>>());
        x.set_type(j.at("type").get<AnnotationsType>());
    }

    inline void to_json(json & j, const ListRootsResult & x) {
        j = json::object();
        j["description"] = x.get_description();
        j["properties"] = x.get_properties();
        j["required"] = x.get_required();
        j["type"] = x.get_type();
    }

    inline void from_json(const json & j, ListToolsResultProperties& x) {
        x.set_meta(j.at("_meta").get<PurpleMeta>());
        x.set_next_cursor(j.at("nextCursor").get<Cursor>());
        x.set_tools(j.at("tools").get<Messages>());
    }

    inline void to_json(json & j, const ListToolsResultProperties & x) {
        j = json::object();
        j["_meta"] = x.get_meta();
        j["nextCursor"] = x.get_next_cursor();
        j["tools"] = x.get_tools();
    }

    inline void from_json(const json & j, ListToolsResult& x) {
        x.set_description(j.at("description").get<std::string>());
        x.set_properties(j.at("properties").get<ListToolsResultProperties>());
        x.set_required(j.at("required").get<std::vector<std::string>>());
        x.set_type(j.at("type").get<AnnotationsType>());
    }

    inline void to_json(json & j, const ListToolsResult & x) {
        j = json::object();
        j["description"] = x.get_description();
        j["properties"] = x.get_properties();
        j["required"] = x.get_required();
        j["type"] = x.get_type();
    }

    inline void from_json(const json & j, FriskyProperties& x) {
        x.set_data(j.at("data").get<PurpleData>());
        x.set_level(j.at("level").get<AnnotationsClass>());
        x.set_logger(j.at("logger").get<Cursor>());
    }

    inline void to_json(json & j, const FriskyProperties & x) {
        j = json::object();
        j["data"] = x.get_data();
        j["level"] = x.get_level();
        j["logger"] = x.get_logger();
    }

    inline void from_json(const json & j, CunningParams& x) {
        x.set_properties(j.at("properties").get<FriskyProperties>());
        x.set_required(j.at("required").get<std::vector<std::string>>());
        x.set_type(j.at("type").get<AnnotationsType>());
    }

    inline void to_json(json & j, const CunningParams & x) {
        j = json::object();
        j["properties"] = x.get_properties();
        j["required"] = x.get_required();
        j["type"] = x.get_type();
    }

    inline void from_json(const json & j, LoggingMessageNotificationProperties& x) {
        x.set_method(j.at("method").get<TypeClass>());
        x.set_params(j.at("params").get<CunningParams>());
    }

    inline void to_json(json & j, const LoggingMessageNotificationProperties & x) {
        j = json::object();
        j["method"] = x.get_method();
        j["params"] = x.get_params();
    }

    inline void from_json(const json & j, LoggingMessageNotification& x) {
        x.set_description(j.at("description").get<std::string>());
        x.set_properties(j.at("properties").get<LoggingMessageNotificationProperties>());
        x.set_required(j.at("required").get<std::vector<std::string>>());
        x.set_type(j.at("type").get<AnnotationsType>());
    }

    inline void to_json(json & j, const LoggingMessageNotification & x) {
        j = json::object();
        j["description"] = x.get_description();
        j["properties"] = x.get_properties();
        j["required"] = x.get_required();
        j["type"] = x.get_type();
    }

    inline void from_json(const json & j, ModelHintProperties& x) {
        x.set_name(j.at("name").get<Cursor>());
    }

    inline void to_json(json & j, const ModelHintProperties & x) {
        j = json::object();
        j["name"] = x.get_name();
    }

    inline void from_json(const json & j, ModelHint& x) {
        x.set_description(j.at("description").get<std::string>());
        x.set_properties(j.at("properties").get<ModelHintProperties>());
        x.set_type(j.at("type").get<AnnotationsType>());
    }

    inline void to_json(json & j, const ModelHint & x) {
        j = json::object();
        j["description"] = x.get_description();
        j["properties"] = x.get_properties();
        j["type"] = x.get_type();
    }

    inline void from_json(const json & j, ModelPreferencesProperties& x) {
        x.set_cost_priority(j.at("costPriority").get<Priority>());
        x.set_hints(j.at("hints").get<Audience>());
        x.set_intelligence_priority(j.at("intelligencePriority").get<Priority>());
        x.set_speed_priority(j.at("speedPriority").get<Priority>());
    }

    inline void to_json(json & j, const ModelPreferencesProperties & x) {
        j = json::object();
        j["costPriority"] = x.get_cost_priority();
        j["hints"] = x.get_hints();
        j["intelligencePriority"] = x.get_intelligence_priority();
        j["speedPriority"] = x.get_speed_priority();
    }

    inline void from_json(const json & j, ModelPreferences& x) {
        x.set_description(j.at("description").get<std::string>());
        x.set_properties(j.at("properties").get<ModelPreferencesProperties>());
        x.set_type(j.at("type").get<AnnotationsType>());
    }

    inline void to_json(json & j, const ModelPreferences & x) {
        j = json::object();
        j["description"] = x.get_description();
        j["properties"] = x.get_properties();
        j["type"] = x.get_type();
    }

    inline void from_json(const json & j, NotificationProperties& x) {
        x.set_method(j.at("method").get<Name>());
        x.set_params(j.at("params").get<Result>());
    }

    inline void to_json(json & j, const NotificationProperties & x) {
        j = json::object();
        j["method"] = x.get_method();
        j["params"] = x.get_params();
    }

    inline void from_json(const json & j, Notification& x) {
        x.set_properties(j.at("properties").get<NotificationProperties>());
        x.set_required(j.at("required").get<std::vector<std::string>>());
        x.set_type(j.at("type").get<AnnotationsType>());
    }

    inline void to_json(json & j, const Notification & x) {
        j = json::object();
        j["properties"] = x.get_properties();
        j["required"] = x.get_required();
        j["type"] = x.get_type();
    }

    inline void from_json(const json & j, PaginatedRequestProperties& x) {
        x.set_method(j.at("method").get<Name>());
        x.set_params(j.at("params").get<AmbitiousParams>());
    }

    inline void to_json(json & j, const PaginatedRequestProperties & x) {
        j = json::object();
        j["method"] = x.get_method();
        j["params"] = x.get_params();
    }

    inline void from_json(const json & j, PaginatedRequest& x) {
        x.set_properties(j.at("properties").get<PaginatedRequestProperties>());
        x.set_required(j.at("required").get<std::vector<std::string>>());
        x.set_type(j.at("type").get<AnnotationsType>());
    }

    inline void to_json(json & j, const PaginatedRequest & x) {
        j = json::object();
        j["properties"] = x.get_properties();
        j["required"] = x.get_required();
        j["type"] = x.get_type();
    }

    inline void from_json(const json & j, PaginatedResultProperties& x) {
        x.set_meta(j.at("_meta").get<PurpleMeta>());
        x.set_next_cursor(j.at("nextCursor").get<Cursor>());
    }

    inline void to_json(json & j, const PaginatedResultProperties & x) {
        j = json::object();
        j["_meta"] = x.get_meta();
        j["nextCursor"] = x.get_next_cursor();
    }

    inline void from_json(const json & j, PaginatedResult& x) {
        x.set_properties(j.at("properties").get<PaginatedResultProperties>());
        x.set_type(j.at("type").get<AnnotationsType>());
    }

    inline void to_json(json & j, const PaginatedResult & x) {
        j = json::object();
        j["properties"] = x.get_properties();
        j["type"] = x.get_type();
    }

    inline void from_json(const json & j, MischievousProperties& x) {
        x.set_message(j.at("message").get<Cursor>());
        x.set_progress(j.at("progress").get<Cursor>());
        x.set_progress_token(j.at("progressToken").get<AnnotationsClass>());
        x.set_total(j.at("total").get<Cursor>());
    }

    inline void to_json(json & j, const MischievousProperties & x) {
        j = json::object();
        j["message"] = x.get_message();
        j["progress"] = x.get_progress();
        j["progressToken"] = x.get_progress_token();
        j["total"] = x.get_total();
    }

    inline void from_json(const json & j, MagentaParams& x) {
        x.set_properties(j.at("properties").get<MischievousProperties>());
        x.set_required(j.at("required").get<std::vector<std::string>>());
        x.set_type(j.at("type").get<AnnotationsType>());
    }

    inline void to_json(json & j, const MagentaParams & x) {
        j = json::object();
        j["properties"] = x.get_properties();
        j["required"] = x.get_required();
        j["type"] = x.get_type();
    }

    inline void from_json(const json & j, ProgressNotificationProperties& x) {
        x.set_method(j.at("method").get<TypeClass>());
        x.set_params(j.at("params").get<MagentaParams>());
    }

    inline void to_json(json & j, const ProgressNotificationProperties & x) {
        j = json::object();
        j["method"] = x.get_method();
        j["params"] = x.get_params();
    }

    inline void from_json(const json & j, ProgressNotification& x) {
        x.set_description(j.at("description").get<std::string>());
        x.set_properties(j.at("properties").get<ProgressNotificationProperties>());
        x.set_required(j.at("required").get<std::vector<std::string>>());
        x.set_type(j.at("type").get<AnnotationsType>());
    }

    inline void to_json(json & j, const ProgressNotification & x) {
        j = json::object();
        j["description"] = x.get_description();
        j["properties"] = x.get_properties();
        j["required"] = x.get_required();
        j["type"] = x.get_type();
    }

    inline void from_json(const json & j, ProgressToken& x) {
        x.set_description(j.at("description").get<std::string>());
        x.set_type(j.at("type").get<std::vector<TypeElement>>());
    }

    inline void to_json(json & j, const ProgressToken & x) {
        j = json::object();
        j["description"] = x.get_description();
        j["type"] = x.get_type();
    }

    inline void from_json(const json & j, PromptProperties& x) {
        x.set_arguments(j.at("arguments").get<Audience>());
        x.set_description(j.at("description").get<Cursor>());
        x.set_name(j.at("name").get<Cursor>());
    }

    inline void to_json(json & j, const PromptProperties & x) {
        j = json::object();
        j["arguments"] = x.get_arguments();
        j["description"] = x.get_description();
        j["name"] = x.get_name();
    }

    inline void from_json(const json & j, Prompt& x) {
        x.set_description(j.at("description").get<std::string>());
        x.set_properties(j.at("properties").get<PromptProperties>());
        x.set_required(j.at("required").get<std::vector<std::string>>());
        x.set_type(j.at("type").get<AnnotationsType>());
    }

    inline void to_json(json & j, const Prompt & x) {
        j = json::object();
        j["description"] = x.get_description();
        j["properties"] = x.get_properties();
        j["required"] = x.get_required();
        j["type"] = x.get_type();
    }

    inline void from_json(const json & j, PromptArgumentProperties& x) {
        x.set_description(j.at("description").get<Cursor>());
        x.set_name(j.at("name").get<Cursor>());
        x.set_required(j.at("required").get<Cursor>());
    }

    inline void to_json(json & j, const PromptArgumentProperties & x) {
        j = json::object();
        j["description"] = x.get_description();
        j["name"] = x.get_name();
        j["required"] = x.get_required();
    }

    inline void from_json(const json & j, PromptArgument& x) {
        x.set_description(j.at("description").get<std::string>());
        x.set_properties(j.at("properties").get<PromptArgumentProperties>());
        x.set_required(j.at("required").get<std::vector<std::string>>());
        x.set_type(j.at("type").get<AnnotationsType>());
    }

    inline void to_json(json & j, const PromptArgument & x) {
        j = json::object();
        j["description"] = x.get_description();
        j["properties"] = x.get_properties();
        j["required"] = x.get_required();
        j["type"] = x.get_type();
    }

    inline void from_json(const json & j, PromptMessageProperties& x) {
        x.set_content(j.at("content").get<ClientNotification>());
        x.set_role(j.at("role").get<EmptyResult>());
    }

    inline void to_json(json & j, const PromptMessageProperties & x) {
        j = json::object();
        j["content"] = x.get_content();
        j["role"] = x.get_role();
    }

    inline void from_json(const json & j, Message& x) {
        x.set_description(j.at("description").get<std::string>());
        x.set_properties(j.at("properties").get<PromptMessageProperties>());
        x.set_required(j.at("required").get<std::vector<std::string>>());
        x.set_type(j.at("type").get<AnnotationsType>());
    }

    inline void to_json(json & j, const Message & x) {
        j = json::object();
        j["description"] = x.get_description();
        j["properties"] = x.get_properties();
        j["required"] = x.get_required();
        j["type"] = x.get_type();
    }

    inline void from_json(const json & j, PromptReferenceProperties& x) {
        x.set_name(j.at("name").get<Cursor>());
        x.set_type(j.at("type").get<TypeClass>());
    }

    inline void to_json(json & j, const PromptReferenceProperties & x) {
        j = json::object();
        j["name"] = x.get_name();
        j["type"] = x.get_type();
    }

    inline void from_json(const json & j, PromptReference& x) {
        x.set_description(j.at("description").get<std::string>());
        x.set_properties(j.at("properties").get<PromptReferenceProperties>());
        x.set_required(j.at("required").get<std::vector<std::string>>());
        x.set_type(j.at("type").get<AnnotationsType>());
    }

    inline void to_json(json & j, const PromptReference & x) {
        j = json::object();
        j["description"] = x.get_description();
        j["properties"] = x.get_properties();
        j["required"] = x.get_required();
        j["type"] = x.get_type();
    }

    inline void from_json(const json & j, BraggadociousProperties& x) {
        x.set_uri(j.at("uri").get<BlobClass>());
    }

    inline void to_json(json & j, const BraggadociousProperties & x) {
        j = json::object();
        j["uri"] = x.get_uri();
    }

    inline void from_json(const json & j, FriskyParams& x) {
        x.set_properties(j.at("properties").get<BraggadociousProperties>());
        x.set_required(j.at("required").get<std::vector<Required>>());
        x.set_type(j.at("type").get<AnnotationsType>());
    }

    inline void to_json(json & j, const FriskyParams & x) {
        j = json::object();
        j["properties"] = x.get_properties();
        j["required"] = x.get_required();
        j["type"] = x.get_type();
    }

    inline void from_json(const json & j, ReadResourceRequestProperties& x) {
        x.set_method(j.at("method").get<TypeClass>());
        x.set_params(j.at("params").get<FriskyParams>());
    }

    inline void to_json(json & j, const ReadResourceRequestProperties & x) {
        j = json::object();
        j["method"] = x.get_method();
        j["params"] = x.get_params();
    }

    inline void from_json(const json & j, ReadResourceRequest& x) {
        x.set_description(j.at("description").get<std::string>());
        x.set_properties(j.at("properties").get<ReadResourceRequestProperties>());
        x.set_required(j.at("required").get<std::vector<std::string>>());
        x.set_type(j.at("type").get<AnnotationsType>());
    }

    inline void to_json(json & j, const ReadResourceRequest & x) {
        j = json::object();
        j["description"] = x.get_description();
        j["properties"] = x.get_properties();
        j["required"] = x.get_required();
        j["type"] = x.get_type();
    }

    inline void from_json(const json & j, ReadResourceResultProperties& x) {
        x.set_meta(j.at("_meta").get<PurpleMeta>());
        x.set_contents(j.at("contents").get<ContentClass>());
    }

    inline void to_json(json & j, const ReadResourceResultProperties & x) {
        j = json::object();
        j["_meta"] = x.get_meta();
        j["contents"] = x.get_contents();
    }

    inline void from_json(const json & j, ReadResourceResult& x) {
        x.set_description(j.at("description").get<std::string>());
        x.set_properties(j.at("properties").get<ReadResourceResultProperties>());
        x.set_required(j.at("required").get<std::vector<std::string>>());
        x.set_type(j.at("type").get<AnnotationsType>());
    }

    inline void to_json(json & j, const ReadResourceResult & x) {
        j = json::object();
        j["description"] = x.get_description();
        j["properties"] = x.get_properties();
        j["required"] = x.get_required();
        j["type"] = x.get_type();
    }

    inline void from_json(const json & j, RequestProperties& x) {
        x.set_method(j.at("method").get<Name>());
        x.set_params(j.at("params").get<HilariousParams>());
    }

    inline void to_json(json & j, const RequestProperties & x) {
        j = json::object();
        j["method"] = x.get_method();
        j["params"] = x.get_params();
    }

    inline void from_json(const json & j, RequestClass& x) {
        x.set_properties(j.at("properties").get<RequestProperties>());
        x.set_required(j.at("required").get<std::vector<std::string>>());
        x.set_type(j.at("type").get<AnnotationsType>());
    }

    inline void to_json(json & j, const RequestClass & x) {
        j = json::object();
        j["properties"] = x.get_properties();
        j["required"] = x.get_required();
        j["type"] = x.get_type();
    }

    inline void from_json(const json & j, ResourceProperties& x) {
        x.set_annotations(j.at("annotations").get<AnnotationsClass>());
        x.set_description(j.at("description").get<Cursor>());
        x.set_mime_type(j.at("mimeType").get<Cursor>());
        x.set_name(j.at("name").get<Cursor>());
        x.set_size(j.at("size").get<Cursor>());
        x.set_uri(j.at("uri").get<BlobClass>());
    }

    inline void to_json(json & j, const ResourceProperties & x) {
        j = json::object();
        j["annotations"] = x.get_annotations();
        j["description"] = x.get_description();
        j["mimeType"] = x.get_mime_type();
        j["name"] = x.get_name();
        j["size"] = x.get_size();
        j["uri"] = x.get_uri();
    }

    inline void from_json(const json & j, Resource& x) {
        x.set_description(j.at("description").get<std::string>());
        x.set_properties(j.at("properties").get<ResourceProperties>());
        x.set_required(j.at("required").get<std::vector<std::string>>());
        x.set_type(j.at("type").get<AnnotationsType>());
    }

    inline void to_json(json & j, const Resource & x) {
        j = json::object();
        j["description"] = x.get_description();
        j["properties"] = x.get_properties();
        j["required"] = x.get_required();
        j["type"] = x.get_type();
    }

    inline void from_json(const json & j, ResourceContentsProperties& x) {
        x.set_mime_type(j.at("mimeType").get<Cursor>());
        x.set_uri(j.at("uri").get<BlobClass>());
    }

    inline void to_json(json & j, const ResourceContentsProperties & x) {
        j = json::object();
        j["mimeType"] = x.get_mime_type();
        j["uri"] = x.get_uri();
    }

    inline void from_json(const json & j, ResourceContents& x) {
        x.set_description(j.at("description").get<std::string>());
        x.set_properties(j.at("properties").get<ResourceContentsProperties>());
        x.set_required(j.at("required").get<std::vector<Required>>());
        x.set_type(j.at("type").get<AnnotationsType>());
    }

    inline void to_json(json & j, const ResourceContents & x) {
        j = json::object();
        j["description"] = x.get_description();
        j["properties"] = x.get_properties();
        j["required"] = x.get_required();
        j["type"] = x.get_type();
    }

    inline void from_json(const json & j, ResourceReferenceProperties& x) {
        x.set_type(j.at("type").get<TypeClass>());
        x.set_uri(j.at("uri").get<BlobClass>());
    }

    inline void to_json(json & j, const ResourceReferenceProperties & x) {
        j = json::object();
        j["type"] = x.get_type();
        j["uri"] = x.get_uri();
    }

    inline void from_json(const json & j, ResourceReference& x) {
        x.set_description(j.at("description").get<std::string>());
        x.set_properties(j.at("properties").get<ResourceReferenceProperties>());
        x.set_required(j.at("required").get<std::vector<std::string>>());
        x.set_type(j.at("type").get<AnnotationsType>());
    }

    inline void to_json(json & j, const ResourceReference & x) {
        j = json::object();
        j["description"] = x.get_description();
        j["properties"] = x.get_properties();
        j["required"] = x.get_required();
        j["type"] = x.get_type();
    }

    inline void from_json(const json & j, ResourceTemplateProperties& x) {
        x.set_annotations(j.at("annotations").get<AnnotationsClass>());
        x.set_description(j.at("description").get<Cursor>());
        x.set_mime_type(j.at("mimeType").get<Cursor>());
        x.set_name(j.at("name").get<Cursor>());
        x.set_uri_template(j.at("uriTemplate").get<BlobClass>());
    }

    inline void to_json(json & j, const ResourceTemplateProperties & x) {
        j = json::object();
        j["annotations"] = x.get_annotations();
        j["description"] = x.get_description();
        j["mimeType"] = x.get_mime_type();
        j["name"] = x.get_name();
        j["uriTemplate"] = x.get_uri_template();
    }

    inline void from_json(const json & j, ResourceTemplate& x) {
        x.set_description(j.at("description").get<std::string>());
        x.set_properties(j.at("properties").get<ResourceTemplateProperties>());
        x.set_required(j.at("required").get<std::vector<std::string>>());
        x.set_type(j.at("type").get<AnnotationsType>());
    }

    inline void to_json(json & j, const ResourceTemplate & x) {
        j = json::object();
        j["description"] = x.get_description();
        j["properties"] = x.get_properties();
        j["required"] = x.get_required();
        j["type"] = x.get_type();
    }

    inline void from_json(const json & j, RootProperties& x) {
        x.set_name(j.at("name").get<Cursor>());
        x.set_uri(j.at("uri").get<BlobClass>());
    }

    inline void to_json(json & j, const RootProperties & x) {
        j = json::object();
        j["name"] = x.get_name();
        j["uri"] = x.get_uri();
    }

    inline void from_json(const json & j, Root& x) {
        x.set_description(j.at("description").get<std::string>());
        x.set_properties(j.at("properties").get<RootProperties>());
        x.set_required(j.at("required").get<std::vector<Required>>());
        x.set_type(j.at("type").get<AnnotationsType>());
    }

    inline void to_json(json & j, const Root & x) {
        j = json::object();
        j["description"] = x.get_description();
        j["properties"] = x.get_properties();
        j["required"] = x.get_required();
        j["type"] = x.get_type();
    }

    inline void from_json(const json & j, ResourcesProperties& x) {
        x.set_list_changed(j.at("listChanged").get<Cursor>());
        x.set_subscribe(j.at("subscribe").get<Cursor>());
    }

    inline void to_json(json & j, const ResourcesProperties & x) {
        j = json::object();
        j["listChanged"] = x.get_list_changed();
        j["subscribe"] = x.get_subscribe();
    }

    inline void from_json(const json & j, Resources& x) {
        x.set_description(j.at("description").get<std::string>());
        x.set_properties(j.at("properties").get<ResourcesProperties>());
        x.set_type(j.at("type").get<AnnotationsType>());
    }

    inline void to_json(json & j, const Resources & x) {
        j = json::object();
        j["description"] = x.get_description();
        j["properties"] = x.get_properties();
        j["type"] = x.get_type();
    }

    inline void from_json(const json & j, ServerCapabilitiesProperties& x) {
        x.set_completions(j.at("completions").get<Sampling>());
        x.set_experimental(j.at("experimental").get<Experimental>());
        x.set_logging(j.at("logging").get<Sampling>());
        x.set_prompts(j.at("prompts").get<Roots>());
        x.set_resources(j.at("resources").get<Resources>());
        x.set_tools(j.at("tools").get<Roots>());
    }

    inline void to_json(json & j, const ServerCapabilitiesProperties & x) {
        j = json::object();
        j["completions"] = x.get_completions();
        j["experimental"] = x.get_experimental();
        j["logging"] = x.get_logging();
        j["prompts"] = x.get_prompts();
        j["resources"] = x.get_resources();
        j["tools"] = x.get_tools();
    }

    inline void from_json(const json & j, ServerCapabilities& x) {
        x.set_description(j.at("description").get<std::string>());
        x.set_properties(j.at("properties").get<ServerCapabilitiesProperties>());
        x.set_type(j.at("type").get<AnnotationsType>());
    }

    inline void to_json(json & j, const ServerCapabilities & x) {
        j = json::object();
        j["description"] = x.get_description();
        j["properties"] = x.get_properties();
        j["type"] = x.get_type();
    }

    inline void from_json(const json & j, Properties1& x) {
        x.set_level(j.at("level").get<AnnotationsClass>());
    }

    inline void to_json(json & j, const Properties1 & x) {
        j = json::object();
        j["level"] = x.get_level();
    }

    inline void from_json(const json & j, MischievousParams& x) {
        x.set_properties(j.at("properties").get<Properties1>());
        x.set_required(j.at("required").get<std::vector<std::string>>());
        x.set_type(j.at("type").get<AnnotationsType>());
    }

    inline void to_json(json & j, const MischievousParams & x) {
        j = json::object();
        j["properties"] = x.get_properties();
        j["required"] = x.get_required();
        j["type"] = x.get_type();
    }

    inline void from_json(const json & j, SetLevelRequestProperties& x) {
        x.set_method(j.at("method").get<TypeClass>());
        x.set_params(j.at("params").get<MischievousParams>());
    }

    inline void to_json(json & j, const SetLevelRequestProperties & x) {
        j = json::object();
        j["method"] = x.get_method();
        j["params"] = x.get_params();
    }

    inline void from_json(const json & j, SetLevelRequest& x) {
        x.set_description(j.at("description").get<std::string>());
        x.set_properties(j.at("properties").get<SetLevelRequestProperties>());
        x.set_required(j.at("required").get<std::vector<std::string>>());
        x.set_type(j.at("type").get<AnnotationsType>());
    }

    inline void to_json(json & j, const SetLevelRequest & x) {
        j = json::object();
        j["description"] = x.get_description();
        j["properties"] = x.get_properties();
        j["required"] = x.get_required();
        j["type"] = x.get_type();
    }

    inline void from_json(const json & j, TextContentProperties& x) {
        x.set_annotations(j.at("annotations").get<AnnotationsClass>());
        x.set_text(j.at("text").get<Cursor>());
        x.set_type(j.at("type").get<TypeClass>());
    }

    inline void to_json(json & j, const TextContentProperties & x) {
        j = json::object();
        j["annotations"] = x.get_annotations();
        j["text"] = x.get_text();
        j["type"] = x.get_type();
    }

    inline void from_json(const json & j, TextContent& x) {
        x.set_description(j.at("description").get<std::string>());
        x.set_properties(j.at("properties").get<TextContentProperties>());
        x.set_required(j.at("required").get<std::vector<std::string>>());
        x.set_type(j.at("type").get<AnnotationsType>());
    }

    inline void to_json(json & j, const TextContent & x) {
        j = json::object();
        j["description"] = x.get_description();
        j["properties"] = x.get_properties();
        j["required"] = x.get_required();
        j["type"] = x.get_type();
    }

    inline void from_json(const json & j, TextResourceContentsProperties& x) {
        x.set_mime_type(j.at("mimeType").get<Cursor>());
        x.set_text(j.at("text").get<Cursor>());
        x.set_uri(j.at("uri").get<BlobClass>());
    }

    inline void to_json(json & j, const TextResourceContentsProperties & x) {
        j = json::object();
        j["mimeType"] = x.get_mime_type();
        j["text"] = x.get_text();
        j["uri"] = x.get_uri();
    }

    inline void from_json(const json & j, TextResourceContents& x) {
        x.set_properties(j.at("properties").get<TextResourceContentsProperties>());
        x.set_required(j.at("required").get<std::vector<std::string>>());
        x.set_type(j.at("type").get<AnnotationsType>());
    }

    inline void to_json(json & j, const TextResourceContents & x) {
        j = json::object();
        j["properties"] = x.get_properties();
        j["required"] = x.get_required();
        j["type"] = x.get_type();
    }

    inline void from_json(const json & j, PropertiesProperties& x) {
        x.set_additional_properties(j.at("additionalProperties").get<Sampling>());
        x.set_type(j.at("type").get<AnnotationsType>());
    }

    inline void to_json(json & j, const PropertiesProperties & x) {
        j = json::object();
        j["additionalProperties"] = x.get_additional_properties();
        j["type"] = x.get_type();
    }

    inline void from_json(const json & j, InputSchemaProperties& x) {
        x.set_properties(j.at("properties").get<PropertiesProperties>());
        x.set_required(j.at("required").get<StopSequences>());
        x.set_type(j.at("type").get<TypeClass>());
    }

    inline void to_json(json & j, const InputSchemaProperties & x) {
        j = json::object();
        j["properties"] = x.get_properties();
        j["required"] = x.get_required();
        j["type"] = x.get_type();
    }

    inline void from_json(const json & j, InputSchema& x) {
        x.set_description(j.at("description").get<std::string>());
        x.set_properties(j.at("properties").get<InputSchemaProperties>());
        x.set_required(j.at("required").get<std::vector<std::string>>());
        x.set_type(j.at("type").get<AnnotationsType>());
    }

    inline void to_json(json & j, const InputSchema & x) {
        j = json::object();
        j["description"] = x.get_description();
        j["properties"] = x.get_properties();
        j["required"] = x.get_required();
        j["type"] = x.get_type();
    }

    inline void from_json(const json & j, ToolProperties& x) {
        x.set_annotations(j.at("annotations").get<AnnotationsClass>());
        x.set_description(j.at("description").get<Cursor>());
        x.set_input_schema(j.at("inputSchema").get<InputSchema>());
        x.set_name(j.at("name").get<Cursor>());
    }

    inline void to_json(json & j, const ToolProperties & x) {
        j = json::object();
        j["annotations"] = x.get_annotations();
        j["description"] = x.get_description();
        j["inputSchema"] = x.get_input_schema();
        j["name"] = x.get_name();
    }

    inline void from_json(const json & j, Tool& x) {
        x.set_description(j.at("description").get<std::string>());
        x.set_properties(j.at("properties").get<ToolProperties>());
        x.set_required(j.at("required").get<std::vector<std::string>>());
        x.set_type(j.at("type").get<AnnotationsType>());
    }

    inline void to_json(json & j, const Tool & x) {
        j = json::object();
        j["description"] = x.get_description();
        j["properties"] = x.get_properties();
        j["required"] = x.get_required();
        j["type"] = x.get_type();
    }

    inline void from_json(const json & j, ToolAnnotationsProperties& x) {
        x.set_destructive_hint(j.at("destructiveHint").get<Cursor>());
        x.set_idempotent_hint(j.at("idempotentHint").get<Cursor>());
        x.set_open_world_hint(j.at("openWorldHint").get<Cursor>());
        x.set_read_only_hint(j.at("readOnlyHint").get<Cursor>());
        x.set_title(j.at("title").get<Cursor>());
    }

    inline void to_json(json & j, const ToolAnnotationsProperties & x) {
        j = json::object();
        j["destructiveHint"] = x.get_destructive_hint();
        j["idempotentHint"] = x.get_idempotent_hint();
        j["openWorldHint"] = x.get_open_world_hint();
        j["readOnlyHint"] = x.get_read_only_hint();
        j["title"] = x.get_title();
    }

    inline void from_json(const json & j, ToolAnnotations& x) {
        x.set_description(j.at("description").get<std::string>());
        x.set_properties(j.at("properties").get<ToolAnnotationsProperties>());
        x.set_type(j.at("type").get<AnnotationsType>());
    }

    inline void to_json(json & j, const ToolAnnotations & x) {
        j = json::object();
        j["description"] = x.get_description();
        j["properties"] = x.get_properties();
        j["type"] = x.get_type();
    }

    inline void from_json(const json & j, Definitions& x) {
        x.set_annotations(j.at("Annotations").get<Annotations>());
        x.set_audio_content(j.at("AudioContent").get<Content>());
        x.set_blob_resource_contents(j.at("BlobResourceContents").get<BlobResourceContents>());
        x.set_call_tool_request(j.at("CallToolRequest").get<CallToolRequest>());
        x.set_call_tool_result(j.at("CallToolResult").get<CallToolResult>());
        x.set_cancelled_notification(j.at("CancelledNotification").get<CancelledNotification>());
        x.set_client_capabilities(j.at("ClientCapabilities").get<ClientCapabilities>());
        x.set_client_notification(j.at("ClientNotification").get<ClientNotification>());
        x.set_client_request(j.at("ClientRequest").get<ClientNotification>());
        x.set_client_result(j.at("ClientResult").get<ClientNotification>());
        x.set_complete_request(j.at("CompleteRequest").get<CompleteRequest>());
        x.set_complete_result(j.at("CompleteResult").get<CompleteResult>());
        x.set_create_message_request(j.at("CreateMessageRequest").get<CreateMessageRequest>());
        x.set_create_message_result(j.at("CreateMessageResult").get<CreateMessageResult>());
        x.set_cursor(j.at("Cursor").get<Cursor>());
        x.set_embedded_resource(j.at("EmbeddedResource").get<EmbeddedResource>());
        x.set_empty_result(j.at("EmptyResult").get<EmptyResult>());
        x.set_get_prompt_request(j.at("GetPromptRequest").get<GetPromptRequest>());
        x.set_get_prompt_result(j.at("GetPromptResult").get<GetPromptResult>());
        x.set_image_content(j.at("ImageContent").get<Content>());
        x.set_implementation(j.at("Implementation").get<Implementation>());
        x.set_initialize_request(j.at("InitializeRequest").get<InitializeRequest>());
        x.set_initialize_result(j.at("InitializeResult").get<InitializeResult>());
        x.set_initialized_notification(j.at("InitializedNotification").get<EdNotification>());
        x.set_jsonrpc_batch_request(j.at("JSONRPCBatchRequest").get<JsonrpcBatchRequest>());
        x.set_jsonrpc_batch_response(j.at("JSONRPCBatchResponse").get<JsonrpcBatchRequest>());
        x.set_jsonrpc_error(j.at("JSONRPCError").get<JsonrpcError>());
        x.set_jsonrpc_message(j.at("JSONRPCMessage").get<JsonrpcMessage>());
        x.set_jsonrpc_notification(j.at("JSONRPCNotification").get<JsonrpcNotification>());
        x.set_jsonrpc_request(j.at("JSONRPCRequest").get<JsonrpcRequest>());
        x.set_jsonrpc_response(j.at("JSONRPCResponse").get<JsonrpcResponse>());
        x.set_list_prompts_request(j.at("ListPromptsRequest").get<ListSRequest>());
        x.set_list_prompts_result(j.at("ListPromptsResult").get<ListPromptsResult>());
        x.set_list_resource_templates_request(j.at("ListResourceTemplatesRequest").get<ListSRequest>());
        x.set_list_resource_templates_result(j.at("ListResourceTemplatesResult").get<ListResourceTemplatesResult>());
        x.set_list_resources_request(j.at("ListResourcesRequest").get<ListSRequest>());
        x.set_list_resources_result(j.at("ListResourcesResult").get<ListResourcesResult>());
        x.set_list_roots_request(j.at("ListRootsRequest").get<Request>());
        x.set_list_roots_result(j.at("ListRootsResult").get<ListRootsResult>());
        x.set_list_tools_request(j.at("ListToolsRequest").get<ListSRequest>());
        x.set_list_tools_result(j.at("ListToolsResult").get<ListToolsResult>());
        x.set_logging_level(j.at("LoggingLevel").get<LoggingLevel>());
        x.set_logging_message_notification(j.at("LoggingMessageNotification").get<LoggingMessageNotification>());
        x.set_model_hint(j.at("ModelHint").get<ModelHint>());
        x.set_model_preferences(j.at("ModelPreferences").get<ModelPreferences>());
        x.set_notification(j.at("Notification").get<Notification>());
        x.set_paginated_request(j.at("PaginatedRequest").get<PaginatedRequest>());
        x.set_paginated_result(j.at("PaginatedResult").get<PaginatedResult>());
        x.set_ping_request(j.at("PingRequest").get<Request>());
        x.set_progress_notification(j.at("ProgressNotification").get<ProgressNotification>());
        x.set_progress_token(j.at("ProgressToken").get<ProgressToken>());
        x.set_prompt(j.at("Prompt").get<Prompt>());
        x.set_prompt_argument(j.at("PromptArgument").get<PromptArgument>());
        x.set_prompt_list_changed_notification(j.at("PromptListChangedNotification").get<EdNotification>());
        x.set_prompt_message(j.at("PromptMessage").get<Message>());
        x.set_prompt_reference(j.at("PromptReference").get<PromptReference>());
        x.set_read_resource_request(j.at("ReadResourceRequest").get<ReadResourceRequest>());
        x.set_read_resource_result(j.at("ReadResourceResult").get<ReadResourceResult>());
        x.set_request(j.at("Request").get<RequestClass>());
        x.set_request_id(j.at("RequestId").get<ProgressToken>());
        x.set_resource(j.at("Resource").get<Resource>());
        x.set_resource_contents(j.at("ResourceContents").get<ResourceContents>());
        x.set_resource_list_changed_notification(j.at("ResourceListChangedNotification").get<EdNotification>());
        x.set_resource_reference(j.at("ResourceReference").get<ResourceReference>());
        x.set_resource_template(j.at("ResourceTemplate").get<ResourceTemplate>());
        x.set_resource_updated_notification(j.at("ResourceUpdatedNotification").get<ReadResourceRequest>());
        x.set_result(j.at("Result").get<Result>());
        x.set_role(j.at("Role").get<LoggingLevel>());
        x.set_root(j.at("Root").get<Root>());
        x.set_roots_list_changed_notification(j.at("RootsListChangedNotification").get<EdNotification>());
        x.set_sampling_message(j.at("SamplingMessage").get<Message>());
        x.set_server_capabilities(j.at("ServerCapabilities").get<ServerCapabilities>());
        x.set_server_notification(j.at("ServerNotification").get<ClientNotification>());
        x.set_server_request(j.at("ServerRequest").get<ClientNotification>());
        x.set_server_result(j.at("ServerResult").get<ClientNotification>());
        x.set_set_level_request(j.at("SetLevelRequest").get<SetLevelRequest>());
        x.set_subscribe_request(j.at("SubscribeRequest").get<ReadResourceRequest>());
        x.set_text_content(j.at("TextContent").get<TextContent>());
        x.set_text_resource_contents(j.at("TextResourceContents").get<TextResourceContents>());
        x.set_tool(j.at("Tool").get<Tool>());
        x.set_tool_annotations(j.at("ToolAnnotations").get<ToolAnnotations>());
        x.set_tool_list_changed_notification(j.at("ToolListChangedNotification").get<EdNotification>());
        x.set_unsubscribe_request(j.at("UnsubscribeRequest").get<ReadResourceRequest>());
    }

    inline void to_json(json & j, const Definitions & x) {
        j = json::object();
        j["Annotations"] = x.get_annotations();
        j["AudioContent"] = x.get_audio_content();
        j["BlobResourceContents"] = x.get_blob_resource_contents();
        j["CallToolRequest"] = x.get_call_tool_request();
        j["CallToolResult"] = x.get_call_tool_result();
        j["CancelledNotification"] = x.get_cancelled_notification();
        j["ClientCapabilities"] = x.get_client_capabilities();
        j["ClientNotification"] = x.get_client_notification();
        j["ClientRequest"] = x.get_client_request();
        j["ClientResult"] = x.get_client_result();
        j["CompleteRequest"] = x.get_complete_request();
        j["CompleteResult"] = x.get_complete_result();
        j["CreateMessageRequest"] = x.get_create_message_request();
        j["CreateMessageResult"] = x.get_create_message_result();
        j["Cursor"] = x.get_cursor();
        j["EmbeddedResource"] = x.get_embedded_resource();
        j["EmptyResult"] = x.get_empty_result();
        j["GetPromptRequest"] = x.get_get_prompt_request();
        j["GetPromptResult"] = x.get_get_prompt_result();
        j["ImageContent"] = x.get_image_content();
        j["Implementation"] = x.get_implementation();
        j["InitializeRequest"] = x.get_initialize_request();
        j["InitializeResult"] = x.get_initialize_result();
        j["InitializedNotification"] = x.get_initialized_notification();
        j["JSONRPCBatchRequest"] = x.get_jsonrpc_batch_request();
        j["JSONRPCBatchResponse"] = x.get_jsonrpc_batch_response();
        j["JSONRPCError"] = x.get_jsonrpc_error();
        j["JSONRPCMessage"] = x.get_jsonrpc_message();
        j["JSONRPCNotification"] = x.get_jsonrpc_notification();
        j["JSONRPCRequest"] = x.get_jsonrpc_request();
        j["JSONRPCResponse"] = x.get_jsonrpc_response();
        j["ListPromptsRequest"] = x.get_list_prompts_request();
        j["ListPromptsResult"] = x.get_list_prompts_result();
        j["ListResourceTemplatesRequest"] = x.get_list_resource_templates_request();
        j["ListResourceTemplatesResult"] = x.get_list_resource_templates_result();
        j["ListResourcesRequest"] = x.get_list_resources_request();
        j["ListResourcesResult"] = x.get_list_resources_result();
        j["ListRootsRequest"] = x.get_list_roots_request();
        j["ListRootsResult"] = x.get_list_roots_result();
        j["ListToolsRequest"] = x.get_list_tools_request();
        j["ListToolsResult"] = x.get_list_tools_result();
        j["LoggingLevel"] = x.get_logging_level();
        j["LoggingMessageNotification"] = x.get_logging_message_notification();
        j["ModelHint"] = x.get_model_hint();
        j["ModelPreferences"] = x.get_model_preferences();
        j["Notification"] = x.get_notification();
        j["PaginatedRequest"] = x.get_paginated_request();
        j["PaginatedResult"] = x.get_paginated_result();
        j["PingRequest"] = x.get_ping_request();
        j["ProgressNotification"] = x.get_progress_notification();
        j["ProgressToken"] = x.get_progress_token();
        j["Prompt"] = x.get_prompt();
        j["PromptArgument"] = x.get_prompt_argument();
        j["PromptListChangedNotification"] = x.get_prompt_list_changed_notification();
        j["PromptMessage"] = x.get_prompt_message();
        j["PromptReference"] = x.get_prompt_reference();
        j["ReadResourceRequest"] = x.get_read_resource_request();
        j["ReadResourceResult"] = x.get_read_resource_result();
        j["Request"] = x.get_request();
        j["RequestId"] = x.get_request_id();
        j["Resource"] = x.get_resource();
        j["ResourceContents"] = x.get_resource_contents();
        j["ResourceListChangedNotification"] = x.get_resource_list_changed_notification();
        j["ResourceReference"] = x.get_resource_reference();
        j["ResourceTemplate"] = x.get_resource_template();
        j["ResourceUpdatedNotification"] = x.get_resource_updated_notification();
        j["Result"] = x.get_result();
        j["Role"] = x.get_role();
        j["Root"] = x.get_root();
        j["RootsListChangedNotification"] = x.get_roots_list_changed_notification();
        j["SamplingMessage"] = x.get_sampling_message();
        j["ServerCapabilities"] = x.get_server_capabilities();
        j["ServerNotification"] = x.get_server_notification();
        j["ServerRequest"] = x.get_server_request();
        j["ServerResult"] = x.get_server_result();
        j["SetLevelRequest"] = x.get_set_level_request();
        j["SubscribeRequest"] = x.get_subscribe_request();
        j["TextContent"] = x.get_text_content();
        j["TextResourceContents"] = x.get_text_resource_contents();
        j["Tool"] = x.get_tool();
        j["ToolAnnotations"] = x.get_tool_annotations();
        j["ToolListChangedNotification"] = x.get_tool_list_changed_notification();
        j["UnsubscribeRequest"] = x.get_unsubscribe_request();
    }

    inline void from_json(const json & j, Schema& x) {
        x.set_schema(j.at("$schema").get<std::string>());
        x.set_definitions(j.at("definitions").get<Definitions>());
    }

    inline void to_json(json & j, const Schema & x) {
        j = json::object();
        j["$schema"] = x.get_schema();
        j["definitions"] = x.get_definitions();
    }

    inline void from_json(const json & j, TypeElement & x) {
        if (j == "boolean") x = TypeElement::BOOLEAN;
        else if (j == "integer") x = TypeElement::INTEGER;
        else if (j == "number") x = TypeElement::NUMBER;
        else if (j == "string") x = TypeElement::STRING;
        else { throw std::runtime_error("Input JSON does not conform to schema!"); }
    }

    inline void to_json(json & j, const TypeElement & x) {
        switch (x) {
            case TypeElement::BOOLEAN: j = "boolean"; break;
            case TypeElement::INTEGER: j = "integer"; break;
            case TypeElement::NUMBER: j = "number"; break;
            case TypeElement::STRING: j = "string"; break;
            default: throw std::runtime_error("Unexpected value in enumeration \"TypeElement\": " + std::to_string(static_cast<int>(x)));
        }
    }

    inline void from_json(const json & j, AnnotationsType & x) {
        if (j == "object") x = AnnotationsType::OBJECT;
        else { throw std::runtime_error("Input JSON does not conform to schema!"); }
    }

    inline void to_json(json & j, const AnnotationsType & x) {
        switch (x) {
            case AnnotationsType::OBJECT: j = "object"; break;
            default: throw std::runtime_error("Unexpected value in enumeration \"AnnotationsType\": " + std::to_string(static_cast<int>(x)));
        }
    }

    inline void from_json(const json & j, Required & x) {
        if (j == "byte") x = Required::BYTE;
        else if (j == "uri") x = Required::URI;
        else if (j == "uri-template") x = Required::URI_TEMPLATE;
        else { throw std::runtime_error("Input JSON does not conform to schema!"); }
    }

    inline void to_json(json & j, const Required & x) {
        switch (x) {
            case Required::BYTE: j = "byte"; break;
            case Required::URI: j = "uri"; break;
            case Required::URI_TEMPLATE: j = "uri-template"; break;
            default: throw std::runtime_error("Unexpected value in enumeration \"Required\": " + std::to_string(static_cast<int>(x)));
        }
    }
}
