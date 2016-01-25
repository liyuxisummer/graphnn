#ifndef GRAPH_STRUCT_H
#define GRAPH_STRUCT_H

#include <vector>
#include <map>
#include <iostream>

template<typename T>
class LinkedTable
{
public:
		LinkedTable()
		{
			n = ncap = 0;
			head.clear();
		}
		
		inline void AddEntry(int head_id, T content)
		{			
			if (head_id >= n)
			{				
				if (head_id + 1 > ncap)
				{
					ncap = std::max(ncap * 2, head_id + 1);
					head.resize(ncap);	
					for (int i = n; i < head_id + 1; ++i)
						head[i].clear();
				}
				n = head_id + 1;
			}
			
			head[head_id].push_back(content);
		}
		
		inline void Resize(int new_n)
		{
			if (new_n > ncap)
			{
				ncap = std::max(ncap * 2, new_n);
				head.resize(ncap);
			}
			n = new_n;
			for (int i = 0; i < n; ++i)
				head[i].clear();
		}
		
		int n;
		std::vector< std::vector<T> > head;
private:
		int ncap;		
};

template<typename T>
class GraphStruct
{
public:
	GraphStruct();
	~GraphStruct();
	
	void AddEdge(int idx, T x, T y);	
	void AddNode(int subg_id, T n_idx);
	void Resize(unsigned _num_subgraph, unsigned _num_nodes = 0);
	void TopSort(std::vector<std::pair<T, T> >& sorted_edges);
	
	LinkedTable< std::pair<int, int> >* adj_list;
	LinkedTable< int >* subgraph;
	unsigned num_nodes, num_edges, num_subgraph;
		
	std::vector<int> degree_in;
	std::map<T, int> idx_map;
	std::map<int, T> t_map;
};

template<>
class GraphStruct<int>
{
public:
	GraphStruct()
	{
		adj_list = new LinkedTable< std::pair<int, int> >();
		subgraph = new LinkedTable< int >();
	}
	~GraphStruct()
	{
		delete adj_list;
		delete subgraph;
	}
	
	inline void AddEdge(int idx, int x, int y)
	{
		adj_list->AddEntry(x, std::pair<int, int>(idx, y));
		num_edges++;
	}
		
	inline void AddNode(int subg_id, int n_idx)
	{
		subgraph->AddEntry(subg_id, n_idx);
	}
	
	inline void Resize(unsigned _num_subgraph, unsigned _num_nodes = 0)
	{
		num_nodes = _num_nodes;
		num_edges = 0;
		num_subgraph = _num_subgraph;
		
		adj_list->Resize(num_nodes);
		subgraph->Resize(num_subgraph);
	}
	
	LinkedTable< std::pair<int, int> >* adj_list;
	LinkedTable< int >* subgraph;
	
	unsigned num_nodes, num_edges, num_subgraph;	
};

#endif