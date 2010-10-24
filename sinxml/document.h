#ifndef sinxml_document_h
#define sinxml_document_h

#include <string>

namespace sinxml
{

class Element;

class Document
{
public:
	Document(const std::string& version);
	~Document();
	void Set_root(Element* e);
	Element* Get_root();
	void Save_file(const std::string& filename);
	bool Load_file(const std::string& filename);
private:	
	std::string version;
	Element* root;
};

}

#endif
