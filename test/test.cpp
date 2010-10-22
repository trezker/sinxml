#include "sinxml/sinxml.h"
#include <iostream>

using namespace sinxml;

int main()
{
	Document document("1.0");
	Element* root = new Element("map", "schmap");
	document.Set_root(root);

	Element* platform = new Element("platform", "boom");
	root->Add_child(platform);

	Element* x = new Element("x", "10");
	platform->Add_child(x);
	
	document.Save_file("test.xml");
	
	document.Load_file("test.xml");
	document.Save_file("test_copy.xml");
	
	Element* parent = document.Get_root();
	Children& children = parent->Get_children();
	for(Children::iterator i = children.begin(); i != children.end(); ++i)
	{
		std::cout<<(*i)->Get_name()<<" = "<<(*i)->Get_value()<<std::endl;
		std::cout<<(*i)->Get_child("x")->Get_value()<<std::endl;
	}
	parent->Get_child("x");
	return 0;
}
