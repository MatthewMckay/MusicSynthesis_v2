//
// Created by Matthew McKay on 6/21/15.
//

#include "XmlDomErrorHandler.h"

void XmlDomErrorHandler::fatalError(const xercesc::SAXParseException &exc)
{
    std::cerr<<"Fatal parsing error at line "<< (int)exc.getLineNumber();
    exit(-1);
}