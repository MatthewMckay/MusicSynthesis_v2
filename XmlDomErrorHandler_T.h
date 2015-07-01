//
// Created by Matthew McKay on 6/21/15.
//

#ifndef MUSICSYNTHESIS_V2_XMLDOMERRORHANDLER_H
#define MUSICSYNTHESIS_V2_XMLDOMERRORHANDLER_H

#include <iostream>

#include <xercesc/sax/HandlerBase.hpp>

class XmlDomErrorHandler_T : public xercesc::HandlerBase
{
public:
    void fatalError(const xercesc::SAXParseException & exc);
};


#endif //MUSICSYNTHESIS_V2_XMLDOMERRORHANDLER_H
