//
// Created by Matthew McKay on 6/21/15.
//

#include "XmlDomDocument_T.h"

xercesc::XercesDOMParser * parser = NULL;
xercesc::ErrorHandler *    errorHandler = NULL;

void createParser()
{
    if (!parser)
    {
        xercesc::XMLPlatformUtils::Initialize();
        parser = new xercesc::XercesDOMParser();
        errorHandler = (xercesc::ErrorHandler*) new XmlDomErrorHandler_T();
        parser->setErrorHandler(errorHandler);
    }
}

XmlDomDocument_T::XmlDomDocument_T(const char * xmlfile) : m_doc(NULL)
{
    createParser();
    parser->parse(xmlfile);
    m_doc = parser->adoptDocument();
    c_pos = nullptr;
    prevElemTag = "";
}

XmlDomDocument_T::~XmlDomDocument_T()
{
    if (m_doc) m_doc->release();
    //parser->reset();
    c_pos = nullptr;
    while (!ancestors.empty()) ancestors.pop();
    //xercesc::XMLPlatformUtils::Terminate();
}

std::string XmlDomDocument_T::GetChildValue(const char *parentTag, int parentIndex,
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

std::string XmlDomDocument_T::GetChildAttribute(const char *parentTag, int parentIndex, const char *childTag,
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

int XmlDomDocument_T::GetChildCount(const char *parentTag, int parentIndex, const char *childTag)
{
    XMLCh * temp = xercesc::XMLString::transcode(parentTag);
    xercesc::DOMNodeList * list = m_doc->getElementsByTagName(temp);
    xercesc::XMLString::release(&temp);

    xercesc::DOMElement * parent = dynamic_cast<xercesc::DOMElement*>(list->item((XMLSize_t)parentIndex));
    xercesc::DOMNodeList * childList = parent->getElementsByTagName(xercesc::XMLString::transcode(childTag));
    return (int)childList->getLength();
}
//*************************************************************

/**
 * advances c_pos to its first child if it exists
 */
bool XmlDomDocument_T::GetChild() {
    if (c_pos->getFirstElementChild()){
        ancestors.push(c_pos);
        prevElemTag = xercesc::XMLString::transcode(c_pos->getTagName());
        c_pos = c_pos->getFirstElementChild();
        return true;
    }
    return false;
}

/**
 * advances c_pos to its first child if it exists and returns node tag name
 */
std::string XmlDomDocument_T::GetChildStr() {
    std::string tagName;
    if (c_pos->getFirstElementChild()){
        ancestors.push(c_pos);
        prevElemTag = xercesc::XMLString::transcode(c_pos->getTagName());
        c_pos = c_pos->getFirstElementChild();
        char * temp = xercesc::XMLString::transcode(c_pos->getTagName());
        tagName = temp;
        return tagName;
    }
    return "";
}

/**
 * advances c_pos to its next sibling if it exists
 */
bool XmlDomDocument_T::GetSibling() {
    if (c_pos->getNextElementSibling()) {
        prevElemTag = xercesc::XMLString::transcode(c_pos->getTagName());
        c_pos = c_pos->getNextElementSibling();
        return true;
    }
    return false;
}

/**
 * advances c_pos to its next sibling if it exists and returns node tag name
 */
std::string XmlDomDocument_T::GetSiblingStr() {
    std::string tagName;
    if (c_pos->getNextElementSibling()){
        prevElemTag = xercesc::XMLString::transcode(c_pos->getTagName());
        c_pos = c_pos->getNextElementSibling();
        char * temp = xercesc::XMLString::transcode(c_pos->getTagName());
        tagName = temp;
        return tagName;
    }
    return "";
}

/**
 * returns the total number of immediate children for the current c_pos
 */
int XmlDomDocument_T::GetTotalChildCount() const{
    //necessary to not change the current position
    xercesc::DOMElement * temp = c_pos;
    int rval = 0;
    if(temp->getFirstElementChild()){
        temp = temp->getFirstElementChild();
        rval++;
    }
    while (temp->getNextElementSibling()) {
        temp = temp->getNextElementSibling();
        rval++;
    }
    return rval;
}

/**
 * pops of ancestors from the ancestor stack until on has a sibling
 * separate from FirstDecendantNamed() because this part can be recursive
 */
std::string XmlDomDocument_T::GetSuccessor(const std::set<const std::string> names) {
    if (!ancestors.empty()) {
        //gets first ancestor
        prevElemTag = xercesc::XMLString::transcode(c_pos->getTagName());
        c_pos = ancestors.top();
        ancestors.pop();
        std::string match;
        //checks the siblings for a match
        if (GetSibling()) {
            if (CheckMatch(names, match)) {
                return match;
            }
            return FirstDescendantNamed(names);
        }
        //otherwise gets next ancestor
        return GetSuccessor(names);
    }
    //if there aren't any more ancestors, there are no more matches so return an empty string
    return "";
}

bool XmlDomDocument_T::CheckMatch(const std::set<const std::string> names, std::string &match) {
    char * temp = xercesc::XMLString::transcode(c_pos->getTagName());
    std::string name = temp;
    xercesc::XMLString::release(&temp);
    std::set<const std::string>::iterator it = names.find(name);
    if (it != names.end()){
        match = *it;
        return true;
    }
    return false;
}

/**
 * Takes in a list of element names to search
 * Iterates through each element node in the document depth first
 * At each node
 *      its tag is compared to the list for a match
 *      c_pos is updated
 *      if depth changes, ancestors is updated
 * continues until a match is found or every child node of the root is explored
 */
std::string XmlDomDocument_T::FirstDescendantNamed(const std::set<const std::string> names) {
    //ultimately returns match which contains the matched element tag name
    std::string match;

    //first check depth
    if (GetChild()) {
        //if a match is found return the matched value
        if (CheckMatch(names, match)) {
            return match;
        }
        //recursively call until the bottom is reached or a match is found
        return FirstDescendantNamed(names);
    }
    else if (GetSibling()) {
        //if a match is found return the matched value
        if (CheckMatch(names, match)) {
            return match;
        }
        //recursively call until all siblings are explored
        return FirstDescendantNamed(names);
    }
    //after the last sibling is explored find the next ancestor with a sibling
    return GetSuccessor(names);
}

/**
 * retrieves the specified attribute from the element node to which the document is currently pointed
 */
std::string XmlDomDocument_T::GetElementAttribute(const char * attribute) const{
    // return string
    std::string value;

    //converts the attribute cstring into the necessary XMLCh string
    XMLCh * temp = xercesc::XMLString::transcode(attribute);

    // if the element has the attribute get the value
    if (c_pos->getAttributeNode(temp)){
        char * temp2 = xercesc::XMLString::transcode(c_pos->getAttribute(temp));
        value = temp2;
    }
    else value = "";

    //XMLCh strings must manually be released
    xercesc::XMLString::release(&temp);
    return value;
}

/**
 * Sets the scope for finding elements
 * sets c_pos to new root (FirstDescendantNamed can only search the descendants of this new root)
 * clears the parent stack
 * childTag is a child tag of the document's top element node
 */
void XmlDomDocument_T::SetNewRoot(const char *childTag, int childIndex) {
    xercesc::DOMElement * parent = m_doc->getDocumentElement();

    //retrieves specified element
    xercesc::DOMElement * child =
            dynamic_cast<xercesc::DOMElement*>(parent->getElementsByTagName(
                    xercesc::XMLString::transcode(childTag))->item((XMLSize_t)childIndex));
    // sets the new root
    prevElemTag = "";
    c_pos = child;
    while (!ancestors.empty()) ancestors.pop();
}

/**
 * returns the child count of a specific tag
 */
int XmlDomDocument_T::GetChildCount(const char *childTag) {
    xercesc::DOMElement * parent = m_doc->getDocumentElement();
    xercesc::DOMNodeList * childList = parent->getElementsByTagName(xercesc::XMLString::transcode(childTag));
    return (int)childList->getLength();
}

std::string XmlDomDocument_T::GetPrevElemTag() const {
    return prevElemTag;
}
