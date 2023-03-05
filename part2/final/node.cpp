#include "node.h"
#include "date.h"

#include <string>

bool DateComparisonNode::Evaluate(const Date& date, const string& event) const {
	if (_cmp == Comparison::Less) {
		return date < _date;
	} else if (_cmp == Comparison::LessOrEqual) {
		return date <= _date;
	} else if (_cmp == Comparison::Greater) {
		return date > _date;
	} else if (_cmp == Comparison::GreaterOrEqual) {
		return date >= _date;
	} else if (_cmp == Comparison::Equal) {
		return date == _date;
	} else {
		return date != _date;
	}
}

bool EventComparisonNode::Evaluate(const Date& date, const string& event) const {
	if (_cmp == Comparison::Less) {
		return event < _value;
	} else if (_cmp == Comparison::LessOrEqual) {
		return event <= _value;
	} else if (_cmp == Comparison::Greater) {
		return event > _value;
	} else if (_cmp == Comparison::GreaterOrEqual) {
		return event >= _value;
	} else if (_cmp == Comparison::Equal) {
		return event == _value;
	} else {
		return event != _value;
	}
}

bool LogicalOperationNode::Evaluate(const Date& date, const string& event) const {
	if (_op == LogicalOperation::And) {
		return _left->Evaluate(date, event) && _right->Evaluate(date, event);
	} else {
		return _left->Evaluate(date, event) || _right->Evaluate(date, event);
	}
}

bool EmptyNode::Evaluate(const Date& date, const string& event) const {
	return true;
}

bool AlwaysFalseNode::Evaluate(const Date&, const std::string& event) const {
	return false;
}
