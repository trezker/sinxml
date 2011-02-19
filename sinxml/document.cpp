#include "document.h"
#include "element.h"
#include <fstream>
#include <iostream>

namespace sinxml
{

Document::Document(const std::string& iversion):
version(iversion),
root(NULL)
{
}

Document::~Document()
{
	delete root;
}

void Document::Set_root(Element* e)
{
	root = e;
}

Element* Document::Get_root()
{
	return root;
}

void Document::Save_file(const std::string& filename)
{
	std::ofstream f;
	f.open(filename.c_str());
	
	f<<"<?xml version=\""<<version<<"\"?>"<<std::endl;
	root->Save_file(f, "");
	
	f.close();
}

bool Document::Load_file(const std::string& filename)
{
	if(root)
	{
		delete root;
		root = NULL;
	}
	std::ifstream f;
	f.open(filename.c_str());
	if(!f.is_open())
		return false;

	char b[512];
	f.getline(b, 511);
	std::string line(b);

	int index = line.find("version");
	int qb = line.find_first_of("\"", index);
	int qe = line.find_first_of("\"", qb+1);
	version = line.substr(qb+1, qe-qb-1);

	Element* parent = NULL;
	
	while(!f.eof())
	{
		f.getline(b, 511);
		line = b;
		index = line.find_first_not_of(" \t");
		if(line[index] == '<')
		{
			int nb = line.find_first_not_of(" \t", index+1);
			if(line[nb] == '/')
			{
				if(parent->Get_parent())
					parent = parent->Get_parent();
				else
				{
					root = parent;
					break;
				}
			}
			else
			{
				int ne = line.find_first_of("> \t/", nb+1);
				std::string name = line.substr(nb, ne-nb);
				
				Element *element = new Element(name);

				while(1)
				{
					int key_begin = line.find_first_of("\"", ne+1);
					if(key_begin >= line.npos) break;
					int key_end = line.find_first_of("\"", key_begin+1);
					if(key_end >= line.npos) break;

					int value_begin = line.find_first_of("\"", key_end+1);
					if(value_begin >= line.npos) break;
					int value_end = line.find_first_of("\"", value_begin+1);
					if(value_end >= line.npos) break;

					std::string key = line.substr(key_begin+1, key_end-key_begin-1);
					std::string value = line.substr(value_begin+1, value_end-value_begin-1);
					std::cout<<key<<"="<<value<<std::endl;
					element->Set_attribute(key, value);
					ne = value_end;
				}
				
				if(parent)
				{
					parent->Add_child(element);
				}
				parent = element;
			}
		}
		else if(parent)
		{
			int ne = line.find_last_not_of(" \t");
			std::string value = line.substr(index, ne-index+1);
			parent->Set_value(value);
		}
	}
	
	if(!root)
		delete parent;
	
	f.close();
	return true;
}

}
