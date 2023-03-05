#pragma once

#include <istream>
#include <ostream>
#include <set>
#include <list>
#include <vector>
#include <map>
#include <string>
using namespace std;

class InvertedIndex {
public:
  void Add(const string& document);
  list<size_t> Lookup(const string& word) const;

  const string& GetDocument(size_t id) const {
    return docs[id];
  }

private:
  map<string, list<size_t>> index;
  vector<string> docs;
};

class SearchServer {
public:
  SearchServer() = default;
  explicit SearchServer(istream& document_input);
  void UpdateDocumentBase(istream& document_input);
  void AddQueriesStream(istream& query_input, ostream& search_results_output);

private:
  const size_t MAX_DOC_COUNT = 10'000;
  InvertedIndex index;
};


//#pragma once
//
//#include <istream>
//#include <ostream>
//#include <iostream>
//#include <set>
//#include <list>
//#include <vector>
//#include <map>
//#include <string>
//
//using namespace std;
//
//class InvertedIndex {
//public:
//  void Add(string document, int docid);
//  list<size_t> Lookup(string word);
//
////  const string& GetDocument(size_t id) const {
////    return docs[id];
////  }
//
//private:
//  map<string, list<size_t>> index;
//  //vector<string> docs;
//};
//
//class SearchServer {
//public:
//  SearchServer() = default;
//  explicit SearchServer(istream& document_input);
//  void UpdateDocumentBase(istream& document_input);
//  void AddQueriesStream(istream& query_input, ostream& search_results_output);
//
//private:
//  InvertedIndex index;
//  bool creation = true;
//
//  void Creation();
//};
