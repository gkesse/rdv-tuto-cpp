#include "cHttpStatusCode.h"
#include <iostream>

std::string HTTP_STATUS_REASON(HTTP_STATUS_CODE::eValues _statusCode)
{
    switch (_statusCode)
    {
    case HTTP_STATUS_CODE::Continue_100:
        return "Continue";
    case HTTP_STATUS_CODE::SwitchingProtocol_101:
        return "Switching Protocol";
    case HTTP_STATUS_CODE::Processing_102:
        return "Processing";
    case HTTP_STATUS_CODE::EarlyHints_103:
        return "Early Hints";
    case HTTP_STATUS_CODE::OK_200:
        return "OK";
    case HTTP_STATUS_CODE::Created_201:
        return "Created";
    case HTTP_STATUS_CODE::Accepted_202:
        return "Accepted";
    case HTTP_STATUS_CODE::NonAuthoritativeInformation_203:
        return "Non-Authoritative Information";
    case HTTP_STATUS_CODE::NoContent_204:
        return "No Content";
    case HTTP_STATUS_CODE::ResetContent_205:
        return "Reset Content";
    case HTTP_STATUS_CODE::PartialContent_206:
        return "Partial Content";
    case HTTP_STATUS_CODE::MultiStatus_207:
        return "Multi-Status";
    case HTTP_STATUS_CODE::AlreadyReported_208:
        return "Already Reported";
    case HTTP_STATUS_CODE::IMUsed_226:
        return "IM Used";
    case HTTP_STATUS_CODE::MultipleChoices_300:
        return "Multiple Choices";
    case HTTP_STATUS_CODE::MovedPermanently_301:
        return "Moved Permanently";
    case HTTP_STATUS_CODE::Found_302:
        return "Found";
    case HTTP_STATUS_CODE::SeeOther_303:
        return "See Other";
    case HTTP_STATUS_CODE::NotModified_304:
        return "Not Modified";
    case HTTP_STATUS_CODE::UseProxy_305:
        return "Use Proxy";
    case HTTP_STATUS_CODE::unused_306:
        return "unused";
    case HTTP_STATUS_CODE::TemporaryRedirect_307:
        return "Temporary Redirect";
    case HTTP_STATUS_CODE::PermanentRedirect_308:
        return "Permanent Redirect";
    case HTTP_STATUS_CODE::BadRequest_400:
        return "Bad Request";
    case HTTP_STATUS_CODE::Unauthorized_401:
        return "Unauthorized";
    case HTTP_STATUS_CODE::PaymentRequired_402:
        return "Payment Required";
    case HTTP_STATUS_CODE::Forbidden_403:
        return "Forbidden";
    case HTTP_STATUS_CODE::NotFound_404:
        return "Not Found";
    case HTTP_STATUS_CODE::MethodNotAllowed_405:
        return "Method Not Allowed";
    case HTTP_STATUS_CODE::NotAcceptable_406:
        return "Not Acceptable";
    case HTTP_STATUS_CODE::ProxyAuthenticationRequired_407:
        return "Proxy Authentication Required";
    case HTTP_STATUS_CODE::RequestTimeout_408:
        return "Request Timeout";
    case HTTP_STATUS_CODE::Conflict_409:
        return "Conflict";
    case HTTP_STATUS_CODE::Gone_410:
        return "Gone";
    case HTTP_STATUS_CODE::LengthRequired_411:
        return "Length Required";
    case HTTP_STATUS_CODE::PreconditionFailed_412:
        return "Precondition Failed";
    case HTTP_STATUS_CODE::PayloadTooLarge_413:
        return "Payload Too Large";
    case HTTP_STATUS_CODE::UriTooLong_414:
        return "URI Too Long";
    case HTTP_STATUS_CODE::UnsupportedMediaType_415:
        return "Unsupported Media Type";
    case HTTP_STATUS_CODE::RangeNotSatisfiable_416:
        return "Range Not Satisfiable";
    case HTTP_STATUS_CODE::ExpectationFailed_417:
        return "Expectation Failed";
    case HTTP_STATUS_CODE::ImATeapot_418:
        return "I'm a teapot";
    case HTTP_STATUS_CODE::MisdirectedRequest_421:
        return "Misdirected Request";
    case HTTP_STATUS_CODE::UnprocessableContent_422:
        return "Unprocessable Content";
    case HTTP_STATUS_CODE::Locked_423:
        return "Locked";
    case HTTP_STATUS_CODE::FailedDependency_424:
        return "Failed Dependency";
    case HTTP_STATUS_CODE::TooEarly_425:
        return "Too Early";
    case HTTP_STATUS_CODE::UpgradeRequired_426:
        return "Upgrade Required";
    case HTTP_STATUS_CODE::PreconditionRequired_428:
        return "Precondition Required";
    case HTTP_STATUS_CODE::TooManyRequests_429:
        return "Too Many Requests";
    case HTTP_STATUS_CODE::RequestHeaderFieldsTooLarge_431:
        return "Request Header Fields Too Large";
    case HTTP_STATUS_CODE::UnavailableForLegalReasons_451:
        return "Unavailable For Legal Reasons";
    case HTTP_STATUS_CODE::NotImplemented_501:
        return "Not Implemented";
    case HTTP_STATUS_CODE::BadGateway_502:
        return "Bad Gateway";
    case HTTP_STATUS_CODE::ServiceUnavailable_503:
        return "Service Unavailable";
    case HTTP_STATUS_CODE::GatewayTimeout_504:
        return "Gateway Timeout";
    case HTTP_STATUS_CODE::HttpVersionNotSupported_505:
        return "HTTP Version Not Supported";
    case HTTP_STATUS_CODE::VariantAlsoNegotiates_506:
        return "Variant Also Negotiates";
    case HTTP_STATUS_CODE::InsufficientStorage_507:
        return "Insufficient Storage";
    case HTTP_STATUS_CODE::LoopDetected_508:
        return "Loop Detected";
    case HTTP_STATUS_CODE::NotExtended_510:
        return "Not Extended";
    case HTTP_STATUS_CODE::NetworkAuthenticationRequired_511:
        return "Network Authentication Required";

    default:
    case HTTP_STATUS_CODE::InternalServerError_500:
    {
        std::cout << "[Error]:Le status de la requête HTTP est inconnu."
                  << "|statusCode=" << _statusCode
                  << std::endl;
        return "Internal Server Error";
    }
    }
}
