#ifndef sinxml_element_h
#define sinxml_element_h

#include <string>
#include <vector>
#include <fstream>
#include <map>

namespace sinxml
{

class Element;
typedef std::vector<Element*> Children;
typedef std::map<std::string, std::string> Attributes;

class Element
{
public:
	Element(const std::string& name, const std::string& value = "");
	/* Destroying an element destroys all its children.
	 * */
	~Element();
	void Set_value(const std::string& v);
	const std::string& Get_name();
	const std::string& Get_value();
	Element* Get_parent();
	Children& Get_children();
	Element* Get_child(const std::string& name);
	void Add_child(Element* e);
	void Set_attribute(const std::string& key, const std::string& value);
	const std::string& Get_attribute(const std::string& key) const;
	void Save_file(std::ofstream& f, const std::string& indent);
private:
	std::string name;
	std::string value;
	Children children;
	Attributes attributes;
	Element* parent;
};

}

#endif
