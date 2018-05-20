#ifndef _Asset_H_
#define _Asset_H_

#include <string>

class Asset_Tag;

class Asset
{
public:
	~Asset();

	// Getters + Setters //
	// Getters
	std::string GetName() { return m_Name; }
	// Setters

protected:
	Asset();

	std::string m_Name = "Uninitialized";
	Asset_Tag* m_Tag;

};

#endif // !_Asset_H_
