#ifndef __STRUCTS_H__
#define __STRUCTS_H__


#include "toInclude.h"


//Xml to TAD

void usersXmlToTAD(TAD_community com, xmlNodePtr doc_root);
void postsXmlToTAD(TAD_community com, xmlNodePtr doc_root);
void tagsXmlToTAD(TAD_community com, xmlNodePtr doc_root);


#endif
