#include "String"
#include "String.h"

using namespace MySTRING;

using iterator = typename string::iterator;
using const_iterator = typename string::const_iterator;
using size_type = typename string::size_type;
using reference = typename string::reference;
using const_reference = typename string::const_reference;

string::string():_start(0),_finsh(0),_end_of_storage(0) {

}

string::string(const string& str) {

	
}

void string::deallocate() {

	dataAllocator::deallocate(_start, capacity());
}

void MySTRING::string::allocate(size_type sz, value_type c){

	_start = dataAllocator::allocate(sz);
	_finsh = MySTL::uninitialized_fill_n(_start, sz, c);
	_end_of_storage = _finsh;
}

iterator MySTRING::string::begin(){

	return _start;
}

const_iterator MySTRING::string::cbegin() const {
	
	return _finsh;
}

iterator MySTRING::string::end() {

	return _finsh;
}

const_iterator MySTRING::string::cend() const {

	return _finsh;
}

size_type MySTRING::string::size() const{

	return _finsh - _start;
}

size_type MySTRING::string::length() const{

	return _finsh - _start;
}

size_type MySTRING::string::capacity() const {

	return _end_of_storage - _start;
}

void MySTRING::string::resize(size_type sz, char c) {

	if (sz < size()) {
		_finsh = _finsh - (size() - sz);
	}
	else if (sz < capacity()) {
		
		_finsh = MySTL::uninitialized_fill_n(_finsh, sz, c);
	}
	else {
		size_type oldCap = capacity();
		size_type newCap = (oldCap == 0) ? sz : (oldCap + sz);

		deallocate();
		
		_start = dataAllocator::allocate(newCap);
		_finsh = MySTL::uninitialized_fill_n(_start, sz, c);
		_end_of_storage = _start + newCap;
	}
}

void MySTRING::string::reserver(size_type sz) {

	if (sz <= capacity()) {
		return;
	}

	iterator newStart = dataAllocator::allocate(sz);
	iterator newFinsh = MySTL::uninitialized_copy(_start, _finsh, newStart);
	iterator newEnd = newStart + sz;

	deallocate();

	_start = newStart;
	_finsh = newFinsh;
	_end_of_storage = newEnd;
}

void MySTRING::string::clear() {

	_finsh = _start;
}

bool MySTRING::string::empty(){

	return (size() == 0) ? true : false;
}

void MySTRING::string::shrink_to_fit() {

	size_type oldSize = size();
	iterator newStart = dataAllocator::allocate(oldSize);
	iterator newFinsh = MySTL::uninitialized_copy(_start, _finsh, newStart);
	iterator newEnd = newFinsh;

	deallocate();

	_start = newStart;
	_finsh = newFinsh;
	_end_of_storage = newEnd;
}

reference MySTRING::string::operator[](size_type pos) {

	if (pos >= size()) {
		throw("error: string::operator[] over range\n");
	}
	
	return *(_start + pos);
}

const_reference MySTRING::string::operator[](size_type pos) const {
	
	if (pos >= size()) {
		throw("error: string::operator[] over range\n");
	}

	return *(_start + pos);
}

reference MySTRING::string::at(size_type pos) {

	return operator[](pos);
}

const_reference MySTRING::string::at(size_type pos) const {

	return operator[](pos);
}

reference MySTRING::string::back() {

	if (empty()) {
		throw("error: string::back()\n");
	}
	return *(_finsh - 1);
}

const_reference MySTRING::string::back() const{
	
	if (_start == _finsh ) {
		throw("error: string::back()\n");
	}
	return *(_finsh - 1);
}

reference MySTRING::string::front() {

	if (_start == _finsh) {
		throw("error: string::back()\n");
	}
	return *_start;
}
