#include <Rcpp.h>
#include <iostream>
#include <fstream>
#include "MTDataFrame.h"
#include "MTSubTable.h"
using namespace Rcpp;

MTSubTable::MTSubTable()
  : n_cols(), n_rows(), c_size(), xr(), yr(), df(4) {};

MTSubTable::MTSubTable(int n_cols, int n_rows, double c_size, int xr, int yr) : df(n_cols) {
    this->n_cols = n_cols;
    this->n_rows = n_rows;
    this->c_size = c_size;
    this->xr = xr;
    this->yr = yr;
  }

  void MTSubTable::set_n_cols(double n_cols) {
    this->n_cols = n_cols;
  }

  void MTSubTable::set_n_rows(double n_rows) {
    this->n_rows = n_rows;
  }

  void MTSubTable::set_c_size(double c_size) {
    this->c_size = c_size;
  }

  void MTSubTable::set_xr(double xr) {
    this->xr = xr;
  }

  void MTSubTable::set_yr(double yr) {
    this->yr = yr;
  }

  void MTSubTable::set_df(MTDataFrame df) {
    this->df = df;
  }

  void MTSubTable::table_add_row(const std::vector<MTSubTable::DataType>& row) {
    df.add_row(row);
  }

  int MTSubTable::get_n_cols() {
    return n_cols;
  }

  int MTSubTable::get_n_rows() {
    return n_rows;
  }

  double MTSubTable::get_c_size() {
    return c_size;
  }

  int MTSubTable::get_xr() {
    return xr;
  }

  int MTSubTable::get_yr() {
    return yr;
  }

MTDataFrame MTSubTable::get_df() {
    return df;
  }

Rcpp::DataFrame MTSubTable::subtable_to_r() {
  return df.to_r();
}


void MTSubTable::serialize(std::ofstream& ofs) const {
  ofs.write(reinterpret_cast<const char*>(&n_cols), sizeof(n_cols));
  ofs.write(reinterpret_cast<const char*>(&n_rows), sizeof(n_rows));
  ofs.write(reinterpret_cast<const char*>(&c_size), sizeof(c_size));
  ofs.write(reinterpret_cast<const char*>(&xr), sizeof(xr));
  ofs.write(reinterpret_cast<const char*>(&yr), sizeof(yr));
}

void MTSubTable::deserialize(std::ifstream& ifs) {
  ifs.read(reinterpret_cast<char*>(&n_cols), sizeof(n_cols));
  ifs.read(reinterpret_cast<char*>(&n_rows), sizeof(n_rows));
  ifs.read(reinterpret_cast<char*>(&c_size), sizeof(c_size));
  ifs.read(reinterpret_cast<char*>(&xr), sizeof(xr));
  ifs.read(reinterpret_cast<char*>(&yr), sizeof(yr));
}


// RCPP_MODULE(MTSubTableEx) {
//   class_<MTSubTable>("MTSubTable")
//   .constructor<int,int,double,int,int>()
//   .method("set_n_cols", &MTSubTable::set_n_cols)
//   .method("set_n_rows", &MTSubTable::set_n_rows)
//   .method("set_c_size", &MTSubTable::set_c_size)
//   .method("set_xr", &MTSubTable::set_xr)
//   .method("set_yr", &MTSubTable::set_yr)
//   .method("set_df", &MTSubTable::set_df)
//   .method("get_n_cols", &MTSubTable::get_n_cols)
//   .method("get_n_rows", &MTSubTable::get_n_rows)
//   .method("get_c_size", &MTSubTable::get_c_size)
//   .method("get_xr", &MTSubTable::get_xr)
//   .method("get_yr", &MTSubTable::get_yr)
//   .method("get_df", &MTSubTable::get_df);
// }
