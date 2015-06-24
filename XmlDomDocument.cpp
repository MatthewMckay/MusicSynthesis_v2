//
// Created by Matthew McKay on 6/21/15.
//

#include "XmlDomDocument.h"

xercesc::XercesDOMParser * parser = NULL;
xercesc::ErrorHandler *    errorHandler = NULL;

void createParser()
{
    if (!parser)
    {
        xercesc::XMLPlatformUtils::Initialize();
        parser = new xercesc::XercesDOMParser();
        errorHandler = (xercesc::ErrorHandler*) new XmlDomErrorHandler();
        parser->setErrorHandler(errorHandler);
    }
}

XmlDomDocument::XmlDomDocument(const char * xmlfile) : m_doc(NULL)
{
    createParser();
    parser->parse(xmlfile);
    m_doc = parser->adoptDocument();
}

XmlDomDocument::~XmlDomDocument()
{
    if (m_doc) m_doc->release();
}

std::string XmlDomDocument::getChildValue(const char *parentTag, int parentIndex,
                                          const char *childTag, int childIndex)
{
    XMLCh * temp = xercesc::XMLString::transcode(parentTag);
    xercesc::DOMNodeList * list = m_doc->getElementsByTagName(temp);
    xercesc::XMLString::release(&temp);

    xercesc::DOMElement * parent =
            dynamic_cast<xercesc::DOMElement*>(list->item((XMLSize_t)parentIndex));
    xercesc::DOMElement * child =
            dynamic_cast<xercesc::DOMElement*>(parent->getElementsByTagName(
                    xercesc::XMLString::transcode(childTag))->item((XMLSize_t)childIndex));
    std::string value;
    if (child)
    {
        char * temp2 = xercesc::XMLString::transcode(child->getTextContent());
        value = temp2;
        xercesc::XMLString::release(&temp2);
    }
    else value = "";
    return value;
}

std::string XmlDomDocument::getChildAttribute(const char *parentTag, int parentIndex,const char *childTag,
                                              int childIndex, const char *attributeTag)
{
    XMLCh * temp = xercesc::XMLString::transcode(parentTag);
    xercesc::DOMNodeList * list = m_doc->getElementsByTagName(temp);
    xercesc::XMLString::release(&temp);

    xercesc::DOMElement * parent = dynamic_cast<xercesc::DOMElement*>(list->item((XMLSize_t)parentIndex));
    xercesc::DOMElement * child = dynamic_cast<xercesc::DOMElement*>(parent->getElementsByTagName(
            xercesc::XMLString::transcode(childTag))->item((XMLSize_t)childIndex));

    std::string value;
    if (child)
    {
        temp = xercesc::XMLString::transcode(attributeTag);
        char * temp2 = xercesc::XMLString::transcode(child->getAttribute(temp));
        value = temp2;
        xercesc::XMLString::release(&temp2);
    }
    else value = "";
    return value;
}

int XmlDomDocument::getChildCount(const char *parentTag, int parentIndex, const char *childTag)
{
    XMLCh * temp = xercesc::XMLString::transcode(parentTag);
    xercesc::DOMNodeList * list = m_doc->getElementsByTagName(temp);
    xercesc::XMLString::release(&temp);

    xercesc::DOMElement * parent = dynamic_cast<xercesc::DOMElement*>(list->item((XMLSize_t)parentIndex));
    xercesc::DOMNodeList * childList = parent->getElementsByTagName(xercesc::XMLString::transcode(childTag));
    return (int)childList->getLength();
}