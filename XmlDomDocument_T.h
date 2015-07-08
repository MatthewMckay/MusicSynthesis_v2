//
// Created by Matthew McKay on 6/21/15.
//

#ifndef MUSICSYNTHESIS_V2_XMLDOMDOCUMENT_H
#define MUSICSYNTHESIS_V2_XMLDOMDOCUMENT_H
#include <string>
#include <stack>
#include <set>
#include <vector>
#include <iostream>

#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/dom/DOM.hpp>
#include <xercesc/util/XMLString.hpp>
#include <xercesc/util/PlatformUtils.hpp>

#include "XmlDomErrorHandler_T.h"

class XmlDomDocument_T {
    xercesc::DOMDocument * m_doc;
    xercesc::DOMElement * c_pos; //holds last accessed element in the XML document
    std::stack<xercesc::DOMElement *> ancestors; //holds all ancestors of current c_pos
    std::string prevElemTag;
public:
    XmlDomDocument_T(const char * xmlfile);
    ~XmlDomDocument_T();

    std::string GetChildValue(const char *parentTag, int parentIndex,
                              const char *childTag, int childIndex);
    std::string GetChildAttribute(const char *parentTag, int parentIndex,
                                  const char *childTag, int childIndex,
                                  const char *attributeTag);
    int GetChildCount(const char *parentTag, int parentIndex,
                      const char *childTag);
    //*******************************************************************
    bool GetChild();
    std::string GetChildStr();
    bool GetSibling();
    std::string GetSiblingStr();
    int  GetTotalChildCount() const;
    std::string GetSuccessor(const std::set<const std::string> names);
    bool CheckMatch(const std::set<const std::string> names, std::string &match);
    std::string FirstDescendantNamed(const std::set<const std::string> names);
    std::string GetElementAttribute(const char * attribute) const;
    int  GetChildCount(const char *childTag);
    void SetNewRoot(const char * childTag,  int childIndex);
    std::string GetPrevElemTag() const;

private:
    XmlDomDocument_T(){};
    XmlDomDocument_T(const XmlDomDocument_T &){};
};
#endif //MUSICSYNTHESIS_V2_XMLDOMDOCUMENT_H
