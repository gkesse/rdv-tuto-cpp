#include "cHttpGet.h"
#include "cFile.h"
#include "cMimeType.h"
#include <iostream>

static const std::string DEF_SERVER_HTTP_ROOT = "../../webroot";

cHttpGet::cHttpGet()
{
}

cHttpGet::~cHttpGet()
{
}

void cHttpGet::run(const sRequest &_requestHTTP, std::string &_responseText, std::string &_contentType, STATUS_CODE &_statusCode) const
{
    std::string oFilename = DEF_SERVER_HTTP_ROOT + _requestHTTP.uri;
    cFile oFile(oFilename);
    if (!oFile.exitsFile())
    {
        _statusCode = HTTP_STATUS_CODE::NotFound_404;
        std::cout << "[Error]:La ressource n'a pas ete trouvee."
                  << "|filename=" << oFilename
                  << std::endl;
        return;
    }
    std::string oExtension = oFile.getExtension();
    _contentType = MIME_TYPE(oExtension);
    _responseText = oFile.readBin();
}
