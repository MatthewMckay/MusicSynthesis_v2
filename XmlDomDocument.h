//
// Created by Matthew McKay on 6/21/15.
//

#ifndef MUSICSYNTHESIS_V2_XMLDOMDOCUMENT_H
#define MUSICSYNTHESIS_V2_XMLDOMDOCUMENT_H
#include <string>
#include <iostream>

#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/dom/DOM.hpp>
#include <xercesc/util/XMLString.hpp>
#include <xercesc/util/PlatformUtils.hpp>

#include "XmlDomErrorHandler.h"

class XmlDomDocument {
    xercesc::DOMDocument * m_doc;
public:
    XmlDomDocument(const char * xmlfile);
    ~XmlDomDocument();

    std::string getChildValue(const char * parentTag, int parentIndex,
                              const char * childTag,  int childIndex);
    std::string getChildAttribute(const char * parentTag, int parentIndex,
                                  const char * childTag,  int childIndex,
                                  const char * attributeTag);
    int getChildCount(const char * parentTag, int parentIndex,
                      const char * childTag);

private:
    XmlDomDocument();
    XmlDomDocument(const XmlDomDocument &);
};
#endif //MUSICSYNTHESIS_V2_XMLDOMDOCUMENT_H
