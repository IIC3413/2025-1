
// Generated from IIC3413DBLexer.g4 by ANTLR 4.13.1

#pragma once


#include "antlr4-runtime.h"




class  IIC3413DBLexer : public antlr4::Lexer {
public:
  enum {
    AND = 1, AS = 2, BETWEEN = 3, CREATE = 4, DISTINCT = 5, FROM = 6, INSERT = 7, 
    INTO = 8, INT = 9, LIKE = 10, LIMIT = 11, OR = 12, SELECT = 13, STR = 14, 
    TABLE = 15, VALUES = 16, WHERE = 17, LEFT = 18, OUTER = 19, JOIN = 20, 
    ON = 21, EC = 22, EQ = 23, NE = 24, GT = 25, LT = 26, GE = 27, LE = 28, 
    COMMA = 29, ASTERISK = 30, MINUS = 31, SLASH = 32, PLUS = 33, DOT = 34, 
    L_PAR = 35, R_PAR = 36, INTEGER = 37, STRING = 38, IDENTIFIER = 39, 
    WHITE_SPACE = 40, COMMENT_INPUT = 41, LINE_COMMENT = 42, UNRECOGNIZED = 43
  };

  enum {
    WS_CHANNEL = 2
  };

  explicit IIC3413DBLexer(antlr4::CharStream *input);

  ~IIC3413DBLexer() override;


  std::string getGrammarFileName() const override;

  const std::vector<std::string>& getRuleNames() const override;

  const std::vector<std::string>& getChannelNames() const override;

  const std::vector<std::string>& getModeNames() const override;

  const antlr4::dfa::Vocabulary& getVocabulary() const override;

  antlr4::atn::SerializedATNView getSerializedATN() const override;

  const antlr4::atn::ATN& getATN() const override;

  // By default the static state used to implement the lexer is lazily initialized during the first
  // call to the constructor. You can call this function if you wish to initialize the static state
  // ahead of time.
  static void initialize();

private:

  // Individual action functions triggered by action() above.

  // Individual semantic predicate functions triggered by sempred() above.

};

