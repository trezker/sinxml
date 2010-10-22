#include "element.h"

namespace sinxml
{

Element::Element(const std::string& iname, const std::string& ivalue):
name(iname),
value(ivalue),
parent(NULL)
{
}

Element::~Element()
{
	for(Children::iterator i = children.begin(); i!=children.end(); ++i)
	{
		delete *i;
	}
}

void Element::Set_value(const std::string& v)
{
	value = v;
}

const std::string& Element::Get_name()
{
	return name;
}

const std::string& Element::Get_value()
{
	return value;
}

Element* Element::Get_parent()
{
	return parent;
}

Children& Element::Get_children()
{
	return children;
}

Element* Element::Get_child(const std::string& name)
{
	for(Children::iterator i = children.begin(); i != children.end(); ++i)
	{
		if(name == (*i)->Get_name())
			return *i;
	}
	return NULL;
}

void Element::Add_child(Element* e)
{
	children.push_back(e);
	e->parent = this;
}

void Element::Save_file(std::ofstream& f, const std::string& indent)
{
	f<<indent<<"<"<<name<<">"<<std::endl;
	if(value != "")
		f<<indent<<" "<<value<<std::endl;
	for(Children::iterator i = children.begin(); i!=children.end(); ++i)
	{
		(*i)->Save_file(f, indent + " ");
	}
	f<<indent<<"</"<<name<<">"<<std::endl;
}

}
