#pragma once

#include "date.h"

#include <string>
#include <memory>

using namespace std;

enum class Comparison {
	Less,
	LessOrEqual,
	Greater,
	GreaterOrEqual,
	Equal,
	NotEqual
};

enum class LogicalOperation {
	Or,
	And
};

enum class NodeType {
	DateComp,
	EventComp,
	LogicalOp,
	Empty,
	AlwaysFalseNode
};


class Node {
public:
	Node(const NodeType& type) : _type(type) {}
	virtual bool Evaluate(const Date& date, const string& event) const = 0;
	virtual ~Node() = default;
private:
	const NodeType _type;
};

class DateComparisonNode : public Node {
public:
	DateComparisonNode(const Comparison& cmp, const Date& date)
	: Node(NodeType::DateComp),
	  _cmp(cmp),
	  _date(date) {}

	bool Evaluate(const Date& date, const string& event) const override;
private:
	const Comparison _cmp;
	const Date _date;
};

class EventComparisonNode : public Node {
public:
	EventComparisonNode(const Comparison& cmp, const string& value)
	: Node(NodeType::EventComp),
	  _cmp(cmp),
	  _value(value) {}

	bool Evaluate(const Date& date, const string& event) const override;
private:
	const Comparison _cmp;
	const string _value;
};

class LogicalOperationNode : public Node {
public:
	LogicalOperationNode(const LogicalOperation& operation,
							shared_ptr<Node> left, shared_ptr<Node> right)
	: Node(NodeType::LogicalOp),
	  _op(operation),
	  _left(left),
	  _right(right) {}

	bool Evaluate(const Date& date, const string& event) const override;
private:
	  const LogicalOperation _op;
	  shared_ptr<const Node> _left;
	  shared_ptr<const Node> _right;
};

class EmptyNode : public Node {
public:
	EmptyNode() : Node(NodeType::Empty) {}

	bool Evaluate(const Date& date, const string& event) const override;
};

class AlwaysFalseNode : public Node {
public:
	AlwaysFalseNode() : Node(NodeType::AlwaysFalseNode) {}
	bool Evaluate(const Date&, const std::string& event) const override;
};
