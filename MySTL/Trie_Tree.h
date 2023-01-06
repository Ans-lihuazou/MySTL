#ifndef _TRIE_TREE_H_2023_1_5_
#define _TRIE_TREE_H_2023_1_5_

#include <map>
#include <string>

namespace MyTree {

	class trie_tree {
	public:
		typedef typename trie_tree* pointer;

		trie_tree();
		explicit trie_tree(const char& c_cData, bool bIsEnd = false);

		virtual ~trie_tree();

		
		bool findString(const std::string& str);
		void setString(const std::string& str);

	private:

		bool isExixt();
		pointer findNext(const char& c_cData);
		pointer setNext(const char& c_cData);

		char m_cData;
		bool m_bIsEnd;
		std::map<char ,pointer> m_mapNext;
	};
}

#endif //_TRIE_TREE_H_2023_1_5_