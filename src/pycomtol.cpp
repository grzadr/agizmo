#include <pybind11/pybind11.h>
#include <pybind11/operators.h>
#include <pybind11/stl.h>
#include <exception>
#include "comtol.h"

namespace py = pybind11;
using namespace pybind11::literals;
using namespace ComTol;
using namespace StrTol;

using std::string;

// PYBIND11_MAKE_OPAQUE(string);

PYBIND11_MODULE(pyComTol, m){
    m.def("str_map", &str_map, "source"_a, "header"_a,
          "clean"_a = true, "sep"_a = "\t");
    m.def("str_map_fields", str_map_fields,
          "source"_a, "fields"_a = ";", "values"_a = "=");

    m.def("mapify", py::overload_cast<const vec_str&, const vec_str&>(&vec_str_map), "keys"_a, "values"_a);

    m.def("str_clean", py::overload_cast<const string&, bool, const string&>(&str_clean),
          "source"_a, "ends"_a = true, "strip"_a = "");

    m.def("str_replace_n",
        py::overload_cast<string, const vector<pair<string, string>>&>(
            &str_replace_n_copy<vector<pair<string, string>>>),
        "source"_a, "index"_a);
    m.def("str_replace_n",
        py::overload_cast<string, const umap_str&>(&str_replace_n_copy<umap_str>),
        "source"_a, "index"_a);

    m.def("str_join_fields",
        py::overload_cast<const umap_str_opt&, string, string>(&str_join_fields),
        "ref"_a, "fields"_a=";", "values"_a="=");

    m.def("str_join_fields",
        py::overload_cast<const umap_str_opt&, const vec_str&, string, string>(
            &str_join_fields),
        "ref"_a, "names"_a, "fields"_a=";", "values"_a="=");
}
