#include "search_server.h"
#include "iterator_range.h"
#include "profile.h"
#include "test_runner.h"

#include <algorithm>
#include <iterator>
#include <sstream>
#include <fstream>
#include <iostream>

vector<string> SplitIntoWords(const string& line) {
  istringstream words_input(line);
  return {istream_iterator<string>(words_input), istream_iterator<string>()};
}

vector<string> SplitIntoWordsWithDuration(const string& line, TotalDuration& dest) {
  ADD_DURATION(dest);
  istringstream words_input(line);
  return {istream_iterator<string>(words_input), istream_iterator<string>()};
}

SearchServer::SearchServer(istream& document_input) {
  UpdateDocumentBase(document_input);
}

void SearchServer::UpdateDocumentBase(istream& document_input) {
  InvertedIndex new_index;

  for (string current_document; getline(document_input, current_document); ) {
    new_index.Add(move(current_document));
  }

  index = move(new_index);
}

void SearchServer::AddQueriesStream(
  istream& query_input, ostream& search_results_output
) {
  TotalDuration split("Split");
  TotalDuration idx("Index");
  TotalDuration srt("Sort");
  TotalDuration out("Output");
  TotalDuration cleaning("Cleaning");

  ofstream check("check.txt");
  size_t counter = 0;
  vector<pair<size_t, size_t>> docid_count(MAX_DOC_COUNT, make_pair(0, 0));

  for (string current_query; getline(query_input, current_query); ) {
    const auto words = SplitIntoWordsWithDuration(current_query, split);

    check << docid_count << '\n';
    //map<size_t, size_t> docid_count;
    {
      ADD_DURATION(idx);
      for (const auto& word : words) {
    	for (const size_t docid : index.Lookup(word)) {
    	  docid_count[docid].first = docid;
    	  docid_count[docid].second += 1;
    	}
      }
    }

//    vector<pair<size_t, size_t>> search_results(
//      docid_count.begin(), docid_count.end()
//    );

    {
      ADD_DURATION(srt);
      sort(
//      begin(search_results),
//      end(search_results),
    	begin(docid_count),
		end(docid_count),
		[](pair<size_t, size_t> lhs, pair<size_t, size_t> rhs) {
        	int64_t lhs_docid = lhs.first;
        	auto lhs_hit_count = lhs.second;
        	int64_t rhs_docid = rhs.first;
        	auto rhs_hit_count = rhs.second;
        	return make_pair(lhs_hit_count, -lhs_docid) > make_pair(rhs_hit_count, -rhs_docid);
      	});
//			partial_sort(
//
//			);
    }

    {
      ADD_DURATION(out);
      search_results_output << current_query << ':';
//    	for (auto [docid, hitcount] : Head(search_results, 5)) {
      for (auto [docid, hitcount] : Head(docid_count, 5)) {
    	if (hitcount != 0) {
    	  search_results_output << " {"
    					        << "docid: " << docid << ", "
							    << "hitcount: " << hitcount << '}';
    	}
      }

      search_results_output << endl;
    }

    {
      ADD_DURATION(cleaning);
      for (auto [docid, hitcount] : docid_count) {
    	counter++;
//    	if (hitcount == 0 && docid == 0) {
//    		break;
//    	}
    	docid = 0;
    	hitcount = 0;
      }
    }

    check << docid_count << '\n';

  }
  cerr << counter << '\n';
}

void InvertedIndex::Add(const string& document) {
  docs.push_back(document);

  const size_t docid = docs.size() - 1;
  for (const auto& word : SplitIntoWords(document)) {
    index[word].push_back(docid);
  }
}

list<size_t> InvertedIndex::Lookup(const string& word) const {
  if (auto it = index.find(word); it != index.end()) {
    return it->second;
  } else {
    return {};
  }
}


//#include "search_server.h"
//#include "iterator_range.h"
//
//#include <algorithm>
//#include <iterator>
//#include <sstream>
//#include <iostream>
//#include <utility>
//
//vector<string> SplitIntoWords(string line) {
//  istringstream words_input(move(line));
//  return {istream_iterator<string>(words_input), istream_iterator<string>()};
//}
//
//SearchServer::SearchServer(istream& document_input) {
//  UpdateDocumentBase(document_input);
//}
//
//void SearchServer::UpdateDocumentBase(istream& document_input) {
//	Creation();
//  InvertedIndex new_index;
//
//  int docid = 0;
//  for (string current_document; getline(document_input, current_document); ) {
//    new_index.Add(move(current_document), docid);
//    ++docid;
//  }
//
//  index = move(new_index);
//}
//
//void SearchServer::AddQueriesStream(
//  istream& query_input, ostream& search_results_output
//) {
//  for (string current_query; getline(query_input, current_query); ) {
//  	search_results_output << current_query << ':';
//
//    auto words = SplitIntoWords(move(current_query));
//
//    map<size_t, size_t> docid_count;
//    for (auto word : words) {
//      for (size_t docid : index.Lookup(move(word))) {
//        docid_count[docid]++;
//      }
//    }
//
//    vector<pair<size_t, size_t>> search_results(
//      make_move_iterator(docid_count.begin()),
//			make_move_iterator(docid_count.end())
//    );
//    sort(
//      begin(search_results),
//      end(search_results),
//      [](pair<size_t, size_t> lhs, pair<size_t, size_t> rhs) {
//        int64_t lhs_docid = lhs.first;
//        auto lhs_hit_count = lhs.second;
//        int64_t rhs_docid = rhs.first;
//        auto rhs_hit_count = rhs.second;
//        return make_pair(lhs_hit_count, -lhs_docid) > make_pair(rhs_hit_count, -rhs_docid);
//      }
//    );
//
//    for (auto [docid, hitcount] : Head(search_results, 5)) {
//      search_results_output << " {"
//        << "docid: " << docid << ", "
//        << "hitcount: " << hitcount << '}';
//    }
//    search_results_output << '\n';
//  }
//}
//
//void SearchServer::Creation() {
//	if (creation) {
//		ios_base::sync_with_stdio(false);
//		cin.tie(nullptr);
//		creation = false;
//	}
//}
//
//void InvertedIndex::Add(string document, int docid) {
////  docs.push_back(document);
////
////  const size_t docid = docs.size() - 1;
//  for (auto word : SplitIntoWords(move(document))) {
//    index[move(word)].push_back(docid);
//  }
//}
//
//list<size_t> InvertedIndex::Lookup(string word) {
//  if (auto it = index.find(move(word)); it != index.end()) {
//    return it->second;
//  } else {
//    return {};
//  }
//}
