/**
 * This file is part of toplogy.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef CONFSCANNER_H
#define CONFSCANNER_H

/**
 * Generated Flex class name is yyFlexLexer by default. If we want to use more flex-generated
 * classes we should name them differently. See scanner.l prefix option.
 * 
 * Unfortunately the implementation relies on this trick with redefining class name
 * with a preprocessor macro. See GNU Flex manual, "Generating C++ Scanners" section
 */
//#ifndef __FLEX_LEXER_H
#undef yyFlexLexer
#define yyFlexLexer ConfFlexLexer

#include <FlexLexer.h>
//#endif

// Scanner method signature is defined by this macro. Original yylex() returns int.
// Sinice Bison 3 uses symbol_type, we must change returned type. We also rename it
// to something sane, since you cannot overload return type.
#undef YY_DECL
#define YY_DECL ks_conf::ConfigParser::symbol_type ks_conf::ConfigScanner::getNextToken()

#include "confparser.hh" // this is needed for symbol_type

namespace ks_conf {

// Forward declare interpreter to avoid include. Header is added inimplementation file.
class Config;

class ConfigScanner : public ConfFlexLexer {
public:
   ConfigScanner(Config &driver) :
           driver(driver) {
   }

   virtual ~ConfigScanner() {
   }

   virtual ks_conf::ConfigParser::symbol_type getNextToken();

private:
   Config &driver;
};

}

#endif
