
// Generated from IIC3413DBParser.g4 by ANTLR 4.13.1


#include "IIC3413DBParserVisitor.h"

#include "IIC3413DBParser.h"


using namespace antlrcpp;

using namespace antlr4;

namespace {

struct IIC3413DBParserStaticData final {
  IIC3413DBParserStaticData(std::vector<std::string> ruleNames,
                        std::vector<std::string> literalNames,
                        std::vector<std::string> symbolicNames)
      : ruleNames(std::move(ruleNames)), literalNames(std::move(literalNames)),
        symbolicNames(std::move(symbolicNames)),
        vocabulary(this->literalNames, this->symbolicNames) {}

  IIC3413DBParserStaticData(const IIC3413DBParserStaticData&) = delete;
  IIC3413DBParserStaticData(IIC3413DBParserStaticData&&) = delete;
  IIC3413DBParserStaticData& operator=(const IIC3413DBParserStaticData&) = delete;
  IIC3413DBParserStaticData& operator=(IIC3413DBParserStaticData&&) = delete;

  std::vector<antlr4::dfa::DFA> decisionToDFA;
  antlr4::atn::PredictionContextCache sharedContextCache;
  const std::vector<std::string> ruleNames;
  const std::vector<std::string> literalNames;
  const std::vector<std::string> symbolicNames;
  const antlr4::dfa::Vocabulary vocabulary;
  antlr4::atn::SerializedATNView serializedATN;
  std::unique_ptr<antlr4::atn::ATN> atn;
};

::antlr4::internal::OnceFlag iic3413dbparserParserOnceFlag;
#if ANTLR4_USE_THREAD_LOCAL_CACHE
static thread_local
#endif
IIC3413DBParserStaticData *iic3413dbparserParserStaticData = nullptr;

void iic3413dbparserParserInitialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  if (iic3413dbparserParserStaticData != nullptr) {
    return;
  }
#else
  assert(iic3413dbparserParserStaticData == nullptr);
#endif
  auto staticData = std::make_unique<IIC3413DBParserStaticData>(
    std::vector<std::string>{
      "root", "query", "createQuery", "insertQuery", "selectQuery", "schema", 
      "datatype", "selectStatement", "columnList", "fromStatement", "tableList", 
      "tableListItem", "leftOuterJoin", "outerJoinOn", "outerJoinComp", 
      "table", "whereStatement", "andExpr", "simpleExpr", "comparisonExpr", 
      "likeExpr", "betweenExpr", "columnOrConstant", "column", "constant", 
      "identifier", "limitStatement", "keyword"
    },
    std::vector<std::string>{
      "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", 
      "", "", "", "", "", "';'", "'=='", "'!='", "'>'", "'<'", "'>='", "'<='", 
      "','", "'*'", "'-'", "'/'", "'+'", "'.'", "'('", "')'"
    },
    std::vector<std::string>{
      "", "AND", "AS", "BETWEEN", "CREATE", "DISTINCT", "FROM", "INSERT", 
      "INTO", "INT", "LIKE", "LIMIT", "OR", "SELECT", "STR", "TABLE", "VALUES", 
      "WHERE", "LEFT", "OUTER", "JOIN", "ON", "EC", "EQ", "NE", "GT", "LT", 
      "GE", "LE", "COMMA", "ASTERISK", "MINUS", "SLASH", "PLUS", "DOT", 
      "L_PAR", "R_PAR", "INTEGER", "STRING", "IDENTIFIER", "WHITE_SPACE", 
      "COMMENT_INPUT", "LINE_COMMENT", "UNRECOGNIZED"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,1,43,218,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,6,2,
  	7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,7,
  	14,2,15,7,15,2,16,7,16,2,17,7,17,2,18,7,18,2,19,7,19,2,20,7,20,2,21,7,
  	21,2,22,7,22,2,23,7,23,2,24,7,24,2,25,7,25,2,26,7,26,2,27,7,27,1,0,1,
  	0,1,0,1,1,1,1,1,1,3,1,63,8,1,1,2,1,2,1,2,1,2,1,2,1,2,1,2,5,2,72,8,2,10,
  	2,12,2,75,9,2,1,2,1,2,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,5,3,87,8,3,10,3,
  	12,3,90,9,3,1,3,1,3,1,4,1,4,1,4,3,4,97,8,4,1,4,3,4,100,8,4,1,5,1,5,1,
  	5,1,6,1,6,1,7,1,7,3,7,109,8,7,1,7,1,7,3,7,113,8,7,1,8,1,8,1,8,5,8,118,
  	8,8,10,8,12,8,121,9,8,1,9,1,9,1,9,1,10,1,10,1,10,5,10,129,8,10,10,10,
  	12,10,132,9,10,1,11,1,11,3,11,136,8,11,1,12,1,12,1,12,1,12,1,12,1,12,
  	1,12,1,12,1,12,1,12,1,12,1,12,1,13,1,13,1,13,5,13,153,8,13,10,13,12,13,
  	156,9,13,1,14,1,14,1,14,1,14,1,15,1,15,1,15,3,15,165,8,15,1,16,1,16,1,
  	16,1,17,1,17,1,17,5,17,173,8,17,10,17,12,17,176,9,17,1,18,1,18,1,18,3,
  	18,181,8,18,1,19,1,19,1,19,3,19,186,8,19,1,20,1,20,1,20,1,20,1,21,1,21,
  	1,21,1,21,1,21,1,21,1,22,1,22,3,22,200,8,22,1,23,1,23,1,23,3,23,205,8,
  	23,1,24,1,24,1,25,1,25,3,25,211,8,25,1,26,1,26,1,26,1,27,1,27,1,27,0,
  	0,28,0,2,4,6,8,10,12,14,16,18,20,22,24,26,28,30,32,34,36,38,40,42,44,
  	46,48,50,52,54,0,4,2,0,9,9,14,14,1,0,23,28,1,0,37,38,1,0,1,17,209,0,56,
  	1,0,0,0,2,62,1,0,0,0,4,64,1,0,0,0,6,78,1,0,0,0,8,93,1,0,0,0,10,101,1,
  	0,0,0,12,104,1,0,0,0,14,106,1,0,0,0,16,114,1,0,0,0,18,122,1,0,0,0,20,
  	125,1,0,0,0,22,135,1,0,0,0,24,137,1,0,0,0,26,149,1,0,0,0,28,157,1,0,0,
  	0,30,161,1,0,0,0,32,166,1,0,0,0,34,169,1,0,0,0,36,180,1,0,0,0,38,182,
  	1,0,0,0,40,187,1,0,0,0,42,191,1,0,0,0,44,199,1,0,0,0,46,201,1,0,0,0,48,
  	206,1,0,0,0,50,210,1,0,0,0,52,212,1,0,0,0,54,215,1,0,0,0,56,57,3,2,1,
  	0,57,58,5,0,0,1,58,1,1,0,0,0,59,63,3,4,2,0,60,63,3,6,3,0,61,63,3,8,4,
  	0,62,59,1,0,0,0,62,60,1,0,0,0,62,61,1,0,0,0,63,3,1,0,0,0,64,65,5,4,0,
  	0,65,66,5,15,0,0,66,67,3,50,25,0,67,68,5,35,0,0,68,73,3,10,5,0,69,70,
  	5,29,0,0,70,72,3,10,5,0,71,69,1,0,0,0,72,75,1,0,0,0,73,71,1,0,0,0,73,
  	74,1,0,0,0,74,76,1,0,0,0,75,73,1,0,0,0,76,77,5,36,0,0,77,5,1,0,0,0,78,
  	79,5,7,0,0,79,80,5,8,0,0,80,81,3,50,25,0,81,82,5,16,0,0,82,83,5,35,0,
  	0,83,88,3,48,24,0,84,85,5,29,0,0,85,87,3,48,24,0,86,84,1,0,0,0,87,90,
  	1,0,0,0,88,86,1,0,0,0,88,89,1,0,0,0,89,91,1,0,0,0,90,88,1,0,0,0,91,92,
  	5,36,0,0,92,7,1,0,0,0,93,94,3,14,7,0,94,96,3,18,9,0,95,97,3,32,16,0,96,
  	95,1,0,0,0,96,97,1,0,0,0,97,99,1,0,0,0,98,100,3,52,26,0,99,98,1,0,0,0,
  	99,100,1,0,0,0,100,9,1,0,0,0,101,102,3,50,25,0,102,103,3,12,6,0,103,11,
  	1,0,0,0,104,105,7,0,0,0,105,13,1,0,0,0,106,108,5,13,0,0,107,109,5,5,0,
  	0,108,107,1,0,0,0,108,109,1,0,0,0,109,112,1,0,0,0,110,113,5,30,0,0,111,
  	113,3,16,8,0,112,110,1,0,0,0,112,111,1,0,0,0,113,15,1,0,0,0,114,119,3,
  	46,23,0,115,116,5,29,0,0,116,118,3,46,23,0,117,115,1,0,0,0,118,121,1,
  	0,0,0,119,117,1,0,0,0,119,120,1,0,0,0,120,17,1,0,0,0,121,119,1,0,0,0,
  	122,123,5,6,0,0,123,124,3,20,10,0,124,19,1,0,0,0,125,130,3,22,11,0,126,
  	127,5,29,0,0,127,129,3,22,11,0,128,126,1,0,0,0,129,132,1,0,0,0,130,128,
  	1,0,0,0,130,131,1,0,0,0,131,21,1,0,0,0,132,130,1,0,0,0,133,136,3,24,12,
  	0,134,136,3,30,15,0,135,133,1,0,0,0,135,134,1,0,0,0,136,23,1,0,0,0,137,
  	138,5,35,0,0,138,139,3,50,25,0,139,140,5,18,0,0,140,141,5,19,0,0,141,
  	142,5,20,0,0,142,143,3,50,25,0,143,144,5,21,0,0,144,145,3,26,13,0,145,
  	146,5,36,0,0,146,147,5,2,0,0,147,148,3,50,25,0,148,25,1,0,0,0,149,154,
  	3,28,14,0,150,151,5,1,0,0,151,153,3,28,14,0,152,150,1,0,0,0,153,156,1,
  	0,0,0,154,152,1,0,0,0,154,155,1,0,0,0,155,27,1,0,0,0,156,154,1,0,0,0,
  	157,158,3,46,23,0,158,159,5,23,0,0,159,160,3,46,23,0,160,29,1,0,0,0,161,
  	164,3,50,25,0,162,163,5,2,0,0,163,165,3,50,25,0,164,162,1,0,0,0,164,165,
  	1,0,0,0,165,31,1,0,0,0,166,167,5,17,0,0,167,168,3,34,17,0,168,33,1,0,
  	0,0,169,174,3,36,18,0,170,171,5,1,0,0,171,173,3,36,18,0,172,170,1,0,0,
  	0,173,176,1,0,0,0,174,172,1,0,0,0,174,175,1,0,0,0,175,35,1,0,0,0,176,
  	174,1,0,0,0,177,181,3,38,19,0,178,181,3,40,20,0,179,181,3,42,21,0,180,
  	177,1,0,0,0,180,178,1,0,0,0,180,179,1,0,0,0,181,37,1,0,0,0,182,185,3,
  	44,22,0,183,184,7,1,0,0,184,186,3,44,22,0,185,183,1,0,0,0,185,186,1,0,
  	0,0,186,39,1,0,0,0,187,188,3,46,23,0,188,189,5,10,0,0,189,190,5,38,0,
  	0,190,41,1,0,0,0,191,192,3,46,23,0,192,193,5,3,0,0,193,194,3,48,24,0,
  	194,195,5,1,0,0,195,196,3,48,24,0,196,43,1,0,0,0,197,200,3,46,23,0,198,
  	200,3,48,24,0,199,197,1,0,0,0,199,198,1,0,0,0,200,45,1,0,0,0,201,204,
  	3,50,25,0,202,203,5,34,0,0,203,205,3,50,25,0,204,202,1,0,0,0,204,205,
  	1,0,0,0,205,47,1,0,0,0,206,207,7,2,0,0,207,49,1,0,0,0,208,211,5,39,0,
  	0,209,211,3,54,27,0,210,208,1,0,0,0,210,209,1,0,0,0,211,51,1,0,0,0,212,
  	213,5,11,0,0,213,214,5,37,0,0,214,53,1,0,0,0,215,216,7,3,0,0,216,55,1,
  	0,0,0,18,62,73,88,96,99,108,112,119,130,135,154,164,174,180,185,199,204,
  	210
  };
  staticData->serializedATN = antlr4::atn::SerializedATNView(serializedATNSegment, sizeof(serializedATNSegment) / sizeof(serializedATNSegment[0]));

  antlr4::atn::ATNDeserializer deserializer;
  staticData->atn = deserializer.deserialize(staticData->serializedATN);

  const size_t count = staticData->atn->getNumberOfDecisions();
  staticData->decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    staticData->decisionToDFA.emplace_back(staticData->atn->getDecisionState(i), i);
  }
  iic3413dbparserParserStaticData = staticData.release();
}

}

IIC3413DBParser::IIC3413DBParser(TokenStream *input) : IIC3413DBParser(input, antlr4::atn::ParserATNSimulatorOptions()) {}

IIC3413DBParser::IIC3413DBParser(TokenStream *input, const antlr4::atn::ParserATNSimulatorOptions &options) : Parser(input) {
  IIC3413DBParser::initialize();
  _interpreter = new atn::ParserATNSimulator(this, *iic3413dbparserParserStaticData->atn, iic3413dbparserParserStaticData->decisionToDFA, iic3413dbparserParserStaticData->sharedContextCache, options);
}

IIC3413DBParser::~IIC3413DBParser() {
  delete _interpreter;
}

const atn::ATN& IIC3413DBParser::getATN() const {
  return *iic3413dbparserParserStaticData->atn;
}

std::string IIC3413DBParser::getGrammarFileName() const {
  return "IIC3413DBParser.g4";
}

const std::vector<std::string>& IIC3413DBParser::getRuleNames() const {
  return iic3413dbparserParserStaticData->ruleNames;
}

const dfa::Vocabulary& IIC3413DBParser::getVocabulary() const {
  return iic3413dbparserParserStaticData->vocabulary;
}

antlr4::atn::SerializedATNView IIC3413DBParser::getSerializedATN() const {
  return iic3413dbparserParserStaticData->serializedATN;
}


//----------------- RootContext ------------------------------------------------------------------

IIC3413DBParser::RootContext::RootContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

IIC3413DBParser::QueryContext* IIC3413DBParser::RootContext::query() {
  return getRuleContext<IIC3413DBParser::QueryContext>(0);
}

tree::TerminalNode* IIC3413DBParser::RootContext::EOF() {
  return getToken(IIC3413DBParser::EOF, 0);
}


size_t IIC3413DBParser::RootContext::getRuleIndex() const {
  return IIC3413DBParser::RuleRoot;
}


std::any IIC3413DBParser::RootContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<IIC3413DBParserVisitor*>(visitor))
    return parserVisitor->visitRoot(this);
  else
    return visitor->visitChildren(this);
}

IIC3413DBParser::RootContext* IIC3413DBParser::root() {
  RootContext *_localctx = _tracker.createInstance<RootContext>(_ctx, getState());
  enterRule(_localctx, 0, IIC3413DBParser::RuleRoot);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(56);
    query();
    setState(57);
    match(IIC3413DBParser::EOF);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- QueryContext ------------------------------------------------------------------

IIC3413DBParser::QueryContext::QueryContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

IIC3413DBParser::CreateQueryContext* IIC3413DBParser::QueryContext::createQuery() {
  return getRuleContext<IIC3413DBParser::CreateQueryContext>(0);
}

IIC3413DBParser::InsertQueryContext* IIC3413DBParser::QueryContext::insertQuery() {
  return getRuleContext<IIC3413DBParser::InsertQueryContext>(0);
}

IIC3413DBParser::SelectQueryContext* IIC3413DBParser::QueryContext::selectQuery() {
  return getRuleContext<IIC3413DBParser::SelectQueryContext>(0);
}


size_t IIC3413DBParser::QueryContext::getRuleIndex() const {
  return IIC3413DBParser::RuleQuery;
}


std::any IIC3413DBParser::QueryContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<IIC3413DBParserVisitor*>(visitor))
    return parserVisitor->visitQuery(this);
  else
    return visitor->visitChildren(this);
}

IIC3413DBParser::QueryContext* IIC3413DBParser::query() {
  QueryContext *_localctx = _tracker.createInstance<QueryContext>(_ctx, getState());
  enterRule(_localctx, 2, IIC3413DBParser::RuleQuery);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(62);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case IIC3413DBParser::CREATE: {
        enterOuterAlt(_localctx, 1);
        setState(59);
        createQuery();
        break;
      }

      case IIC3413DBParser::INSERT: {
        enterOuterAlt(_localctx, 2);
        setState(60);
        insertQuery();
        break;
      }

      case IIC3413DBParser::SELECT: {
        enterOuterAlt(_localctx, 3);
        setState(61);
        selectQuery();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- CreateQueryContext ------------------------------------------------------------------

IIC3413DBParser::CreateQueryContext::CreateQueryContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* IIC3413DBParser::CreateQueryContext::CREATE() {
  return getToken(IIC3413DBParser::CREATE, 0);
}

tree::TerminalNode* IIC3413DBParser::CreateQueryContext::TABLE() {
  return getToken(IIC3413DBParser::TABLE, 0);
}

IIC3413DBParser::IdentifierContext* IIC3413DBParser::CreateQueryContext::identifier() {
  return getRuleContext<IIC3413DBParser::IdentifierContext>(0);
}

tree::TerminalNode* IIC3413DBParser::CreateQueryContext::L_PAR() {
  return getToken(IIC3413DBParser::L_PAR, 0);
}

std::vector<IIC3413DBParser::SchemaContext *> IIC3413DBParser::CreateQueryContext::schema() {
  return getRuleContexts<IIC3413DBParser::SchemaContext>();
}

IIC3413DBParser::SchemaContext* IIC3413DBParser::CreateQueryContext::schema(size_t i) {
  return getRuleContext<IIC3413DBParser::SchemaContext>(i);
}

tree::TerminalNode* IIC3413DBParser::CreateQueryContext::R_PAR() {
  return getToken(IIC3413DBParser::R_PAR, 0);
}

std::vector<tree::TerminalNode *> IIC3413DBParser::CreateQueryContext::COMMA() {
  return getTokens(IIC3413DBParser::COMMA);
}

tree::TerminalNode* IIC3413DBParser::CreateQueryContext::COMMA(size_t i) {
  return getToken(IIC3413DBParser::COMMA, i);
}


size_t IIC3413DBParser::CreateQueryContext::getRuleIndex() const {
  return IIC3413DBParser::RuleCreateQuery;
}


std::any IIC3413DBParser::CreateQueryContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<IIC3413DBParserVisitor*>(visitor))
    return parserVisitor->visitCreateQuery(this);
  else
    return visitor->visitChildren(this);
}

IIC3413DBParser::CreateQueryContext* IIC3413DBParser::createQuery() {
  CreateQueryContext *_localctx = _tracker.createInstance<CreateQueryContext>(_ctx, getState());
  enterRule(_localctx, 4, IIC3413DBParser::RuleCreateQuery);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(64);
    match(IIC3413DBParser::CREATE);
    setState(65);
    match(IIC3413DBParser::TABLE);
    setState(66);
    identifier();
    setState(67);
    match(IIC3413DBParser::L_PAR);
    setState(68);
    schema();
    setState(73);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == IIC3413DBParser::COMMA) {
      setState(69);
      match(IIC3413DBParser::COMMA);
      setState(70);
      schema();
      setState(75);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(76);
    match(IIC3413DBParser::R_PAR);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- InsertQueryContext ------------------------------------------------------------------

IIC3413DBParser::InsertQueryContext::InsertQueryContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* IIC3413DBParser::InsertQueryContext::INSERT() {
  return getToken(IIC3413DBParser::INSERT, 0);
}

tree::TerminalNode* IIC3413DBParser::InsertQueryContext::INTO() {
  return getToken(IIC3413DBParser::INTO, 0);
}

IIC3413DBParser::IdentifierContext* IIC3413DBParser::InsertQueryContext::identifier() {
  return getRuleContext<IIC3413DBParser::IdentifierContext>(0);
}

tree::TerminalNode* IIC3413DBParser::InsertQueryContext::VALUES() {
  return getToken(IIC3413DBParser::VALUES, 0);
}

tree::TerminalNode* IIC3413DBParser::InsertQueryContext::L_PAR() {
  return getToken(IIC3413DBParser::L_PAR, 0);
}

std::vector<IIC3413DBParser::ConstantContext *> IIC3413DBParser::InsertQueryContext::constant() {
  return getRuleContexts<IIC3413DBParser::ConstantContext>();
}

IIC3413DBParser::ConstantContext* IIC3413DBParser::InsertQueryContext::constant(size_t i) {
  return getRuleContext<IIC3413DBParser::ConstantContext>(i);
}

tree::TerminalNode* IIC3413DBParser::InsertQueryContext::R_PAR() {
  return getToken(IIC3413DBParser::R_PAR, 0);
}

std::vector<tree::TerminalNode *> IIC3413DBParser::InsertQueryContext::COMMA() {
  return getTokens(IIC3413DBParser::COMMA);
}

tree::TerminalNode* IIC3413DBParser::InsertQueryContext::COMMA(size_t i) {
  return getToken(IIC3413DBParser::COMMA, i);
}


size_t IIC3413DBParser::InsertQueryContext::getRuleIndex() const {
  return IIC3413DBParser::RuleInsertQuery;
}


std::any IIC3413DBParser::InsertQueryContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<IIC3413DBParserVisitor*>(visitor))
    return parserVisitor->visitInsertQuery(this);
  else
    return visitor->visitChildren(this);
}

IIC3413DBParser::InsertQueryContext* IIC3413DBParser::insertQuery() {
  InsertQueryContext *_localctx = _tracker.createInstance<InsertQueryContext>(_ctx, getState());
  enterRule(_localctx, 6, IIC3413DBParser::RuleInsertQuery);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(78);
    match(IIC3413DBParser::INSERT);
    setState(79);
    match(IIC3413DBParser::INTO);
    setState(80);
    identifier();
    setState(81);
    match(IIC3413DBParser::VALUES);
    setState(82);
    match(IIC3413DBParser::L_PAR);
    setState(83);
    constant();
    setState(88);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == IIC3413DBParser::COMMA) {
      setState(84);
      match(IIC3413DBParser::COMMA);
      setState(85);
      constant();
      setState(90);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(91);
    match(IIC3413DBParser::R_PAR);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- SelectQueryContext ------------------------------------------------------------------

IIC3413DBParser::SelectQueryContext::SelectQueryContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

IIC3413DBParser::SelectStatementContext* IIC3413DBParser::SelectQueryContext::selectStatement() {
  return getRuleContext<IIC3413DBParser::SelectStatementContext>(0);
}

IIC3413DBParser::FromStatementContext* IIC3413DBParser::SelectQueryContext::fromStatement() {
  return getRuleContext<IIC3413DBParser::FromStatementContext>(0);
}

IIC3413DBParser::WhereStatementContext* IIC3413DBParser::SelectQueryContext::whereStatement() {
  return getRuleContext<IIC3413DBParser::WhereStatementContext>(0);
}

IIC3413DBParser::LimitStatementContext* IIC3413DBParser::SelectQueryContext::limitStatement() {
  return getRuleContext<IIC3413DBParser::LimitStatementContext>(0);
}


size_t IIC3413DBParser::SelectQueryContext::getRuleIndex() const {
  return IIC3413DBParser::RuleSelectQuery;
}


std::any IIC3413DBParser::SelectQueryContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<IIC3413DBParserVisitor*>(visitor))
    return parserVisitor->visitSelectQuery(this);
  else
    return visitor->visitChildren(this);
}

IIC3413DBParser::SelectQueryContext* IIC3413DBParser::selectQuery() {
  SelectQueryContext *_localctx = _tracker.createInstance<SelectQueryContext>(_ctx, getState());
  enterRule(_localctx, 8, IIC3413DBParser::RuleSelectQuery);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(93);
    selectStatement();
    setState(94);
    fromStatement();
    setState(96);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == IIC3413DBParser::WHERE) {
      setState(95);
      whereStatement();
    }
    setState(99);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == IIC3413DBParser::LIMIT) {
      setState(98);
      limitStatement();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- SchemaContext ------------------------------------------------------------------

IIC3413DBParser::SchemaContext::SchemaContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

IIC3413DBParser::IdentifierContext* IIC3413DBParser::SchemaContext::identifier() {
  return getRuleContext<IIC3413DBParser::IdentifierContext>(0);
}

IIC3413DBParser::DatatypeContext* IIC3413DBParser::SchemaContext::datatype() {
  return getRuleContext<IIC3413DBParser::DatatypeContext>(0);
}


size_t IIC3413DBParser::SchemaContext::getRuleIndex() const {
  return IIC3413DBParser::RuleSchema;
}


std::any IIC3413DBParser::SchemaContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<IIC3413DBParserVisitor*>(visitor))
    return parserVisitor->visitSchema(this);
  else
    return visitor->visitChildren(this);
}

IIC3413DBParser::SchemaContext* IIC3413DBParser::schema() {
  SchemaContext *_localctx = _tracker.createInstance<SchemaContext>(_ctx, getState());
  enterRule(_localctx, 10, IIC3413DBParser::RuleSchema);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(101);
    identifier();
    setState(102);
    datatype();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- DatatypeContext ------------------------------------------------------------------

IIC3413DBParser::DatatypeContext::DatatypeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* IIC3413DBParser::DatatypeContext::STR() {
  return getToken(IIC3413DBParser::STR, 0);
}

tree::TerminalNode* IIC3413DBParser::DatatypeContext::INT() {
  return getToken(IIC3413DBParser::INT, 0);
}


size_t IIC3413DBParser::DatatypeContext::getRuleIndex() const {
  return IIC3413DBParser::RuleDatatype;
}


std::any IIC3413DBParser::DatatypeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<IIC3413DBParserVisitor*>(visitor))
    return parserVisitor->visitDatatype(this);
  else
    return visitor->visitChildren(this);
}

IIC3413DBParser::DatatypeContext* IIC3413DBParser::datatype() {
  DatatypeContext *_localctx = _tracker.createInstance<DatatypeContext>(_ctx, getState());
  enterRule(_localctx, 12, IIC3413DBParser::RuleDatatype);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(104);
    _la = _input->LA(1);
    if (!(_la == IIC3413DBParser::INT

    || _la == IIC3413DBParser::STR)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- SelectStatementContext ------------------------------------------------------------------

IIC3413DBParser::SelectStatementContext::SelectStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* IIC3413DBParser::SelectStatementContext::SELECT() {
  return getToken(IIC3413DBParser::SELECT, 0);
}

tree::TerminalNode* IIC3413DBParser::SelectStatementContext::ASTERISK() {
  return getToken(IIC3413DBParser::ASTERISK, 0);
}

IIC3413DBParser::ColumnListContext* IIC3413DBParser::SelectStatementContext::columnList() {
  return getRuleContext<IIC3413DBParser::ColumnListContext>(0);
}

tree::TerminalNode* IIC3413DBParser::SelectStatementContext::DISTINCT() {
  return getToken(IIC3413DBParser::DISTINCT, 0);
}


size_t IIC3413DBParser::SelectStatementContext::getRuleIndex() const {
  return IIC3413DBParser::RuleSelectStatement;
}


std::any IIC3413DBParser::SelectStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<IIC3413DBParserVisitor*>(visitor))
    return parserVisitor->visitSelectStatement(this);
  else
    return visitor->visitChildren(this);
}

IIC3413DBParser::SelectStatementContext* IIC3413DBParser::selectStatement() {
  SelectStatementContext *_localctx = _tracker.createInstance<SelectStatementContext>(_ctx, getState());
  enterRule(_localctx, 14, IIC3413DBParser::RuleSelectStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(106);
    match(IIC3413DBParser::SELECT);
    setState(108);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 5, _ctx)) {
    case 1: {
      setState(107);
      match(IIC3413DBParser::DISTINCT);
      break;
    }

    default:
      break;
    }
    setState(112);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case IIC3413DBParser::ASTERISK: {
        setState(110);
        match(IIC3413DBParser::ASTERISK);
        break;
      }

      case IIC3413DBParser::AND:
      case IIC3413DBParser::AS:
      case IIC3413DBParser::BETWEEN:
      case IIC3413DBParser::CREATE:
      case IIC3413DBParser::DISTINCT:
      case IIC3413DBParser::FROM:
      case IIC3413DBParser::INSERT:
      case IIC3413DBParser::INTO:
      case IIC3413DBParser::INT:
      case IIC3413DBParser::LIKE:
      case IIC3413DBParser::LIMIT:
      case IIC3413DBParser::OR:
      case IIC3413DBParser::SELECT:
      case IIC3413DBParser::STR:
      case IIC3413DBParser::TABLE:
      case IIC3413DBParser::VALUES:
      case IIC3413DBParser::WHERE:
      case IIC3413DBParser::IDENTIFIER: {
        setState(111);
        columnList();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ColumnListContext ------------------------------------------------------------------

IIC3413DBParser::ColumnListContext::ColumnListContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<IIC3413DBParser::ColumnContext *> IIC3413DBParser::ColumnListContext::column() {
  return getRuleContexts<IIC3413DBParser::ColumnContext>();
}

IIC3413DBParser::ColumnContext* IIC3413DBParser::ColumnListContext::column(size_t i) {
  return getRuleContext<IIC3413DBParser::ColumnContext>(i);
}

std::vector<tree::TerminalNode *> IIC3413DBParser::ColumnListContext::COMMA() {
  return getTokens(IIC3413DBParser::COMMA);
}

tree::TerminalNode* IIC3413DBParser::ColumnListContext::COMMA(size_t i) {
  return getToken(IIC3413DBParser::COMMA, i);
}


size_t IIC3413DBParser::ColumnListContext::getRuleIndex() const {
  return IIC3413DBParser::RuleColumnList;
}


std::any IIC3413DBParser::ColumnListContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<IIC3413DBParserVisitor*>(visitor))
    return parserVisitor->visitColumnList(this);
  else
    return visitor->visitChildren(this);
}

IIC3413DBParser::ColumnListContext* IIC3413DBParser::columnList() {
  ColumnListContext *_localctx = _tracker.createInstance<ColumnListContext>(_ctx, getState());
  enterRule(_localctx, 16, IIC3413DBParser::RuleColumnList);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(114);
    column();
    setState(119);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == IIC3413DBParser::COMMA) {
      setState(115);
      match(IIC3413DBParser::COMMA);
      setState(116);
      column();
      setState(121);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FromStatementContext ------------------------------------------------------------------

IIC3413DBParser::FromStatementContext::FromStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* IIC3413DBParser::FromStatementContext::FROM() {
  return getToken(IIC3413DBParser::FROM, 0);
}

IIC3413DBParser::TableListContext* IIC3413DBParser::FromStatementContext::tableList() {
  return getRuleContext<IIC3413DBParser::TableListContext>(0);
}


size_t IIC3413DBParser::FromStatementContext::getRuleIndex() const {
  return IIC3413DBParser::RuleFromStatement;
}


std::any IIC3413DBParser::FromStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<IIC3413DBParserVisitor*>(visitor))
    return parserVisitor->visitFromStatement(this);
  else
    return visitor->visitChildren(this);
}

IIC3413DBParser::FromStatementContext* IIC3413DBParser::fromStatement() {
  FromStatementContext *_localctx = _tracker.createInstance<FromStatementContext>(_ctx, getState());
  enterRule(_localctx, 18, IIC3413DBParser::RuleFromStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(122);
    match(IIC3413DBParser::FROM);
    setState(123);
    tableList();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- TableListContext ------------------------------------------------------------------

IIC3413DBParser::TableListContext::TableListContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<IIC3413DBParser::TableListItemContext *> IIC3413DBParser::TableListContext::tableListItem() {
  return getRuleContexts<IIC3413DBParser::TableListItemContext>();
}

IIC3413DBParser::TableListItemContext* IIC3413DBParser::TableListContext::tableListItem(size_t i) {
  return getRuleContext<IIC3413DBParser::TableListItemContext>(i);
}

std::vector<tree::TerminalNode *> IIC3413DBParser::TableListContext::COMMA() {
  return getTokens(IIC3413DBParser::COMMA);
}

tree::TerminalNode* IIC3413DBParser::TableListContext::COMMA(size_t i) {
  return getToken(IIC3413DBParser::COMMA, i);
}


size_t IIC3413DBParser::TableListContext::getRuleIndex() const {
  return IIC3413DBParser::RuleTableList;
}


std::any IIC3413DBParser::TableListContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<IIC3413DBParserVisitor*>(visitor))
    return parserVisitor->visitTableList(this);
  else
    return visitor->visitChildren(this);
}

IIC3413DBParser::TableListContext* IIC3413DBParser::tableList() {
  TableListContext *_localctx = _tracker.createInstance<TableListContext>(_ctx, getState());
  enterRule(_localctx, 20, IIC3413DBParser::RuleTableList);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(125);
    tableListItem();
    setState(130);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == IIC3413DBParser::COMMA) {
      setState(126);
      match(IIC3413DBParser::COMMA);
      setState(127);
      tableListItem();
      setState(132);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- TableListItemContext ------------------------------------------------------------------

IIC3413DBParser::TableListItemContext::TableListItemContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

IIC3413DBParser::LeftOuterJoinContext* IIC3413DBParser::TableListItemContext::leftOuterJoin() {
  return getRuleContext<IIC3413DBParser::LeftOuterJoinContext>(0);
}

IIC3413DBParser::TableContext* IIC3413DBParser::TableListItemContext::table() {
  return getRuleContext<IIC3413DBParser::TableContext>(0);
}


size_t IIC3413DBParser::TableListItemContext::getRuleIndex() const {
  return IIC3413DBParser::RuleTableListItem;
}


std::any IIC3413DBParser::TableListItemContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<IIC3413DBParserVisitor*>(visitor))
    return parserVisitor->visitTableListItem(this);
  else
    return visitor->visitChildren(this);
}

IIC3413DBParser::TableListItemContext* IIC3413DBParser::tableListItem() {
  TableListItemContext *_localctx = _tracker.createInstance<TableListItemContext>(_ctx, getState());
  enterRule(_localctx, 22, IIC3413DBParser::RuleTableListItem);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(135);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case IIC3413DBParser::L_PAR: {
        enterOuterAlt(_localctx, 1);
        setState(133);
        leftOuterJoin();
        break;
      }

      case IIC3413DBParser::AND:
      case IIC3413DBParser::AS:
      case IIC3413DBParser::BETWEEN:
      case IIC3413DBParser::CREATE:
      case IIC3413DBParser::DISTINCT:
      case IIC3413DBParser::FROM:
      case IIC3413DBParser::INSERT:
      case IIC3413DBParser::INTO:
      case IIC3413DBParser::INT:
      case IIC3413DBParser::LIKE:
      case IIC3413DBParser::LIMIT:
      case IIC3413DBParser::OR:
      case IIC3413DBParser::SELECT:
      case IIC3413DBParser::STR:
      case IIC3413DBParser::TABLE:
      case IIC3413DBParser::VALUES:
      case IIC3413DBParser::WHERE:
      case IIC3413DBParser::IDENTIFIER: {
        enterOuterAlt(_localctx, 2);
        setState(134);
        table();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- LeftOuterJoinContext ------------------------------------------------------------------

IIC3413DBParser::LeftOuterJoinContext::LeftOuterJoinContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* IIC3413DBParser::LeftOuterJoinContext::L_PAR() {
  return getToken(IIC3413DBParser::L_PAR, 0);
}

std::vector<IIC3413DBParser::IdentifierContext *> IIC3413DBParser::LeftOuterJoinContext::identifier() {
  return getRuleContexts<IIC3413DBParser::IdentifierContext>();
}

IIC3413DBParser::IdentifierContext* IIC3413DBParser::LeftOuterJoinContext::identifier(size_t i) {
  return getRuleContext<IIC3413DBParser::IdentifierContext>(i);
}

tree::TerminalNode* IIC3413DBParser::LeftOuterJoinContext::LEFT() {
  return getToken(IIC3413DBParser::LEFT, 0);
}

tree::TerminalNode* IIC3413DBParser::LeftOuterJoinContext::OUTER() {
  return getToken(IIC3413DBParser::OUTER, 0);
}

tree::TerminalNode* IIC3413DBParser::LeftOuterJoinContext::JOIN() {
  return getToken(IIC3413DBParser::JOIN, 0);
}

tree::TerminalNode* IIC3413DBParser::LeftOuterJoinContext::ON() {
  return getToken(IIC3413DBParser::ON, 0);
}

IIC3413DBParser::OuterJoinOnContext* IIC3413DBParser::LeftOuterJoinContext::outerJoinOn() {
  return getRuleContext<IIC3413DBParser::OuterJoinOnContext>(0);
}

tree::TerminalNode* IIC3413DBParser::LeftOuterJoinContext::R_PAR() {
  return getToken(IIC3413DBParser::R_PAR, 0);
}

tree::TerminalNode* IIC3413DBParser::LeftOuterJoinContext::AS() {
  return getToken(IIC3413DBParser::AS, 0);
}


size_t IIC3413DBParser::LeftOuterJoinContext::getRuleIndex() const {
  return IIC3413DBParser::RuleLeftOuterJoin;
}


std::any IIC3413DBParser::LeftOuterJoinContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<IIC3413DBParserVisitor*>(visitor))
    return parserVisitor->visitLeftOuterJoin(this);
  else
    return visitor->visitChildren(this);
}

IIC3413DBParser::LeftOuterJoinContext* IIC3413DBParser::leftOuterJoin() {
  LeftOuterJoinContext *_localctx = _tracker.createInstance<LeftOuterJoinContext>(_ctx, getState());
  enterRule(_localctx, 24, IIC3413DBParser::RuleLeftOuterJoin);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(137);
    match(IIC3413DBParser::L_PAR);
    setState(138);
    identifier();
    setState(139);
    match(IIC3413DBParser::LEFT);
    setState(140);
    match(IIC3413DBParser::OUTER);
    setState(141);
    match(IIC3413DBParser::JOIN);
    setState(142);
    identifier();
    setState(143);
    match(IIC3413DBParser::ON);
    setState(144);
    outerJoinOn();
    setState(145);
    match(IIC3413DBParser::R_PAR);
    setState(146);
    match(IIC3413DBParser::AS);
    setState(147);
    identifier();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- OuterJoinOnContext ------------------------------------------------------------------

IIC3413DBParser::OuterJoinOnContext::OuterJoinOnContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<IIC3413DBParser::OuterJoinCompContext *> IIC3413DBParser::OuterJoinOnContext::outerJoinComp() {
  return getRuleContexts<IIC3413DBParser::OuterJoinCompContext>();
}

IIC3413DBParser::OuterJoinCompContext* IIC3413DBParser::OuterJoinOnContext::outerJoinComp(size_t i) {
  return getRuleContext<IIC3413DBParser::OuterJoinCompContext>(i);
}

std::vector<tree::TerminalNode *> IIC3413DBParser::OuterJoinOnContext::AND() {
  return getTokens(IIC3413DBParser::AND);
}

tree::TerminalNode* IIC3413DBParser::OuterJoinOnContext::AND(size_t i) {
  return getToken(IIC3413DBParser::AND, i);
}


size_t IIC3413DBParser::OuterJoinOnContext::getRuleIndex() const {
  return IIC3413DBParser::RuleOuterJoinOn;
}


std::any IIC3413DBParser::OuterJoinOnContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<IIC3413DBParserVisitor*>(visitor))
    return parserVisitor->visitOuterJoinOn(this);
  else
    return visitor->visitChildren(this);
}

IIC3413DBParser::OuterJoinOnContext* IIC3413DBParser::outerJoinOn() {
  OuterJoinOnContext *_localctx = _tracker.createInstance<OuterJoinOnContext>(_ctx, getState());
  enterRule(_localctx, 26, IIC3413DBParser::RuleOuterJoinOn);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(149);
    outerJoinComp();
    setState(154);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == IIC3413DBParser::AND) {
      setState(150);
      match(IIC3413DBParser::AND);
      setState(151);
      outerJoinComp();
      setState(156);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- OuterJoinCompContext ------------------------------------------------------------------

IIC3413DBParser::OuterJoinCompContext::OuterJoinCompContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<IIC3413DBParser::ColumnContext *> IIC3413DBParser::OuterJoinCompContext::column() {
  return getRuleContexts<IIC3413DBParser::ColumnContext>();
}

IIC3413DBParser::ColumnContext* IIC3413DBParser::OuterJoinCompContext::column(size_t i) {
  return getRuleContext<IIC3413DBParser::ColumnContext>(i);
}

tree::TerminalNode* IIC3413DBParser::OuterJoinCompContext::EQ() {
  return getToken(IIC3413DBParser::EQ, 0);
}


size_t IIC3413DBParser::OuterJoinCompContext::getRuleIndex() const {
  return IIC3413DBParser::RuleOuterJoinComp;
}


std::any IIC3413DBParser::OuterJoinCompContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<IIC3413DBParserVisitor*>(visitor))
    return parserVisitor->visitOuterJoinComp(this);
  else
    return visitor->visitChildren(this);
}

IIC3413DBParser::OuterJoinCompContext* IIC3413DBParser::outerJoinComp() {
  OuterJoinCompContext *_localctx = _tracker.createInstance<OuterJoinCompContext>(_ctx, getState());
  enterRule(_localctx, 28, IIC3413DBParser::RuleOuterJoinComp);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(157);
    column();
    setState(158);
    match(IIC3413DBParser::EQ);
    setState(159);
    column();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- TableContext ------------------------------------------------------------------

IIC3413DBParser::TableContext::TableContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<IIC3413DBParser::IdentifierContext *> IIC3413DBParser::TableContext::identifier() {
  return getRuleContexts<IIC3413DBParser::IdentifierContext>();
}

IIC3413DBParser::IdentifierContext* IIC3413DBParser::TableContext::identifier(size_t i) {
  return getRuleContext<IIC3413DBParser::IdentifierContext>(i);
}

tree::TerminalNode* IIC3413DBParser::TableContext::AS() {
  return getToken(IIC3413DBParser::AS, 0);
}


size_t IIC3413DBParser::TableContext::getRuleIndex() const {
  return IIC3413DBParser::RuleTable;
}


std::any IIC3413DBParser::TableContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<IIC3413DBParserVisitor*>(visitor))
    return parserVisitor->visitTable(this);
  else
    return visitor->visitChildren(this);
}

IIC3413DBParser::TableContext* IIC3413DBParser::table() {
  TableContext *_localctx = _tracker.createInstance<TableContext>(_ctx, getState());
  enterRule(_localctx, 30, IIC3413DBParser::RuleTable);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(161);
    identifier();
    setState(164);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == IIC3413DBParser::AS) {
      setState(162);
      match(IIC3413DBParser::AS);
      setState(163);
      identifier();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- WhereStatementContext ------------------------------------------------------------------

IIC3413DBParser::WhereStatementContext::WhereStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* IIC3413DBParser::WhereStatementContext::WHERE() {
  return getToken(IIC3413DBParser::WHERE, 0);
}

IIC3413DBParser::AndExprContext* IIC3413DBParser::WhereStatementContext::andExpr() {
  return getRuleContext<IIC3413DBParser::AndExprContext>(0);
}


size_t IIC3413DBParser::WhereStatementContext::getRuleIndex() const {
  return IIC3413DBParser::RuleWhereStatement;
}


std::any IIC3413DBParser::WhereStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<IIC3413DBParserVisitor*>(visitor))
    return parserVisitor->visitWhereStatement(this);
  else
    return visitor->visitChildren(this);
}

IIC3413DBParser::WhereStatementContext* IIC3413DBParser::whereStatement() {
  WhereStatementContext *_localctx = _tracker.createInstance<WhereStatementContext>(_ctx, getState());
  enterRule(_localctx, 32, IIC3413DBParser::RuleWhereStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(166);
    match(IIC3413DBParser::WHERE);
    setState(167);
    andExpr();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- AndExprContext ------------------------------------------------------------------

IIC3413DBParser::AndExprContext::AndExprContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<IIC3413DBParser::SimpleExprContext *> IIC3413DBParser::AndExprContext::simpleExpr() {
  return getRuleContexts<IIC3413DBParser::SimpleExprContext>();
}

IIC3413DBParser::SimpleExprContext* IIC3413DBParser::AndExprContext::simpleExpr(size_t i) {
  return getRuleContext<IIC3413DBParser::SimpleExprContext>(i);
}

std::vector<tree::TerminalNode *> IIC3413DBParser::AndExprContext::AND() {
  return getTokens(IIC3413DBParser::AND);
}

tree::TerminalNode* IIC3413DBParser::AndExprContext::AND(size_t i) {
  return getToken(IIC3413DBParser::AND, i);
}


size_t IIC3413DBParser::AndExprContext::getRuleIndex() const {
  return IIC3413DBParser::RuleAndExpr;
}


std::any IIC3413DBParser::AndExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<IIC3413DBParserVisitor*>(visitor))
    return parserVisitor->visitAndExpr(this);
  else
    return visitor->visitChildren(this);
}

IIC3413DBParser::AndExprContext* IIC3413DBParser::andExpr() {
  AndExprContext *_localctx = _tracker.createInstance<AndExprContext>(_ctx, getState());
  enterRule(_localctx, 34, IIC3413DBParser::RuleAndExpr);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(169);
    simpleExpr();
    setState(174);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == IIC3413DBParser::AND) {
      setState(170);
      match(IIC3413DBParser::AND);
      setState(171);
      simpleExpr();
      setState(176);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- SimpleExprContext ------------------------------------------------------------------

IIC3413DBParser::SimpleExprContext::SimpleExprContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

IIC3413DBParser::ComparisonExprContext* IIC3413DBParser::SimpleExprContext::comparisonExpr() {
  return getRuleContext<IIC3413DBParser::ComparisonExprContext>(0);
}

IIC3413DBParser::LikeExprContext* IIC3413DBParser::SimpleExprContext::likeExpr() {
  return getRuleContext<IIC3413DBParser::LikeExprContext>(0);
}

IIC3413DBParser::BetweenExprContext* IIC3413DBParser::SimpleExprContext::betweenExpr() {
  return getRuleContext<IIC3413DBParser::BetweenExprContext>(0);
}


size_t IIC3413DBParser::SimpleExprContext::getRuleIndex() const {
  return IIC3413DBParser::RuleSimpleExpr;
}


std::any IIC3413DBParser::SimpleExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<IIC3413DBParserVisitor*>(visitor))
    return parserVisitor->visitSimpleExpr(this);
  else
    return visitor->visitChildren(this);
}

IIC3413DBParser::SimpleExprContext* IIC3413DBParser::simpleExpr() {
  SimpleExprContext *_localctx = _tracker.createInstance<SimpleExprContext>(_ctx, getState());
  enterRule(_localctx, 36, IIC3413DBParser::RuleSimpleExpr);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(180);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 13, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(177);
      comparisonExpr();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(178);
      likeExpr();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(179);
      betweenExpr();
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ComparisonExprContext ------------------------------------------------------------------

IIC3413DBParser::ComparisonExprContext::ComparisonExprContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<IIC3413DBParser::ColumnOrConstantContext *> IIC3413DBParser::ComparisonExprContext::columnOrConstant() {
  return getRuleContexts<IIC3413DBParser::ColumnOrConstantContext>();
}

IIC3413DBParser::ColumnOrConstantContext* IIC3413DBParser::ComparisonExprContext::columnOrConstant(size_t i) {
  return getRuleContext<IIC3413DBParser::ColumnOrConstantContext>(i);
}

tree::TerminalNode* IIC3413DBParser::ComparisonExprContext::EQ() {
  return getToken(IIC3413DBParser::EQ, 0);
}

tree::TerminalNode* IIC3413DBParser::ComparisonExprContext::NE() {
  return getToken(IIC3413DBParser::NE, 0);
}

tree::TerminalNode* IIC3413DBParser::ComparisonExprContext::LT() {
  return getToken(IIC3413DBParser::LT, 0);
}

tree::TerminalNode* IIC3413DBParser::ComparisonExprContext::GT() {
  return getToken(IIC3413DBParser::GT, 0);
}

tree::TerminalNode* IIC3413DBParser::ComparisonExprContext::LE() {
  return getToken(IIC3413DBParser::LE, 0);
}

tree::TerminalNode* IIC3413DBParser::ComparisonExprContext::GE() {
  return getToken(IIC3413DBParser::GE, 0);
}


size_t IIC3413DBParser::ComparisonExprContext::getRuleIndex() const {
  return IIC3413DBParser::RuleComparisonExpr;
}


std::any IIC3413DBParser::ComparisonExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<IIC3413DBParserVisitor*>(visitor))
    return parserVisitor->visitComparisonExpr(this);
  else
    return visitor->visitChildren(this);
}

IIC3413DBParser::ComparisonExprContext* IIC3413DBParser::comparisonExpr() {
  ComparisonExprContext *_localctx = _tracker.createInstance<ComparisonExprContext>(_ctx, getState());
  enterRule(_localctx, 38, IIC3413DBParser::RuleComparisonExpr);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(182);
    columnOrConstant();
    setState(185);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 528482304) != 0)) {
      setState(183);
      antlrcpp::downCast<ComparisonExprContext *>(_localctx)->op = _input->LT(1);
      _la = _input->LA(1);
      if (!((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 528482304) != 0))) {
        antlrcpp::downCast<ComparisonExprContext *>(_localctx)->op = _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(184);
      columnOrConstant();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- LikeExprContext ------------------------------------------------------------------

IIC3413DBParser::LikeExprContext::LikeExprContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

IIC3413DBParser::ColumnContext* IIC3413DBParser::LikeExprContext::column() {
  return getRuleContext<IIC3413DBParser::ColumnContext>(0);
}

tree::TerminalNode* IIC3413DBParser::LikeExprContext::LIKE() {
  return getToken(IIC3413DBParser::LIKE, 0);
}

tree::TerminalNode* IIC3413DBParser::LikeExprContext::STRING() {
  return getToken(IIC3413DBParser::STRING, 0);
}


size_t IIC3413DBParser::LikeExprContext::getRuleIndex() const {
  return IIC3413DBParser::RuleLikeExpr;
}


std::any IIC3413DBParser::LikeExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<IIC3413DBParserVisitor*>(visitor))
    return parserVisitor->visitLikeExpr(this);
  else
    return visitor->visitChildren(this);
}

IIC3413DBParser::LikeExprContext* IIC3413DBParser::likeExpr() {
  LikeExprContext *_localctx = _tracker.createInstance<LikeExprContext>(_ctx, getState());
  enterRule(_localctx, 40, IIC3413DBParser::RuleLikeExpr);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(187);
    column();
    setState(188);
    match(IIC3413DBParser::LIKE);
    setState(189);
    match(IIC3413DBParser::STRING);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- BetweenExprContext ------------------------------------------------------------------

IIC3413DBParser::BetweenExprContext::BetweenExprContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

IIC3413DBParser::ColumnContext* IIC3413DBParser::BetweenExprContext::column() {
  return getRuleContext<IIC3413DBParser::ColumnContext>(0);
}

tree::TerminalNode* IIC3413DBParser::BetweenExprContext::BETWEEN() {
  return getToken(IIC3413DBParser::BETWEEN, 0);
}

std::vector<IIC3413DBParser::ConstantContext *> IIC3413DBParser::BetweenExprContext::constant() {
  return getRuleContexts<IIC3413DBParser::ConstantContext>();
}

IIC3413DBParser::ConstantContext* IIC3413DBParser::BetweenExprContext::constant(size_t i) {
  return getRuleContext<IIC3413DBParser::ConstantContext>(i);
}

tree::TerminalNode* IIC3413DBParser::BetweenExprContext::AND() {
  return getToken(IIC3413DBParser::AND, 0);
}


size_t IIC3413DBParser::BetweenExprContext::getRuleIndex() const {
  return IIC3413DBParser::RuleBetweenExpr;
}


std::any IIC3413DBParser::BetweenExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<IIC3413DBParserVisitor*>(visitor))
    return parserVisitor->visitBetweenExpr(this);
  else
    return visitor->visitChildren(this);
}

IIC3413DBParser::BetweenExprContext* IIC3413DBParser::betweenExpr() {
  BetweenExprContext *_localctx = _tracker.createInstance<BetweenExprContext>(_ctx, getState());
  enterRule(_localctx, 42, IIC3413DBParser::RuleBetweenExpr);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(191);
    column();
    setState(192);
    match(IIC3413DBParser::BETWEEN);
    setState(193);
    constant();
    setState(194);
    match(IIC3413DBParser::AND);
    setState(195);
    constant();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ColumnOrConstantContext ------------------------------------------------------------------

IIC3413DBParser::ColumnOrConstantContext::ColumnOrConstantContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

IIC3413DBParser::ColumnContext* IIC3413DBParser::ColumnOrConstantContext::column() {
  return getRuleContext<IIC3413DBParser::ColumnContext>(0);
}

IIC3413DBParser::ConstantContext* IIC3413DBParser::ColumnOrConstantContext::constant() {
  return getRuleContext<IIC3413DBParser::ConstantContext>(0);
}


size_t IIC3413DBParser::ColumnOrConstantContext::getRuleIndex() const {
  return IIC3413DBParser::RuleColumnOrConstant;
}


std::any IIC3413DBParser::ColumnOrConstantContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<IIC3413DBParserVisitor*>(visitor))
    return parserVisitor->visitColumnOrConstant(this);
  else
    return visitor->visitChildren(this);
}

IIC3413DBParser::ColumnOrConstantContext* IIC3413DBParser::columnOrConstant() {
  ColumnOrConstantContext *_localctx = _tracker.createInstance<ColumnOrConstantContext>(_ctx, getState());
  enterRule(_localctx, 44, IIC3413DBParser::RuleColumnOrConstant);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(199);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case IIC3413DBParser::AND:
      case IIC3413DBParser::AS:
      case IIC3413DBParser::BETWEEN:
      case IIC3413DBParser::CREATE:
      case IIC3413DBParser::DISTINCT:
      case IIC3413DBParser::FROM:
      case IIC3413DBParser::INSERT:
      case IIC3413DBParser::INTO:
      case IIC3413DBParser::INT:
      case IIC3413DBParser::LIKE:
      case IIC3413DBParser::LIMIT:
      case IIC3413DBParser::OR:
      case IIC3413DBParser::SELECT:
      case IIC3413DBParser::STR:
      case IIC3413DBParser::TABLE:
      case IIC3413DBParser::VALUES:
      case IIC3413DBParser::WHERE:
      case IIC3413DBParser::IDENTIFIER: {
        enterOuterAlt(_localctx, 1);
        setState(197);
        column();
        break;
      }

      case IIC3413DBParser::INTEGER:
      case IIC3413DBParser::STRING: {
        enterOuterAlt(_localctx, 2);
        setState(198);
        constant();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ColumnContext ------------------------------------------------------------------

IIC3413DBParser::ColumnContext::ColumnContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<IIC3413DBParser::IdentifierContext *> IIC3413DBParser::ColumnContext::identifier() {
  return getRuleContexts<IIC3413DBParser::IdentifierContext>();
}

IIC3413DBParser::IdentifierContext* IIC3413DBParser::ColumnContext::identifier(size_t i) {
  return getRuleContext<IIC3413DBParser::IdentifierContext>(i);
}

tree::TerminalNode* IIC3413DBParser::ColumnContext::DOT() {
  return getToken(IIC3413DBParser::DOT, 0);
}


size_t IIC3413DBParser::ColumnContext::getRuleIndex() const {
  return IIC3413DBParser::RuleColumn;
}


std::any IIC3413DBParser::ColumnContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<IIC3413DBParserVisitor*>(visitor))
    return parserVisitor->visitColumn(this);
  else
    return visitor->visitChildren(this);
}

IIC3413DBParser::ColumnContext* IIC3413DBParser::column() {
  ColumnContext *_localctx = _tracker.createInstance<ColumnContext>(_ctx, getState());
  enterRule(_localctx, 46, IIC3413DBParser::RuleColumn);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(201);
    identifier();
    setState(204);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == IIC3413DBParser::DOT) {
      setState(202);
      match(IIC3413DBParser::DOT);
      setState(203);
      identifier();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ConstantContext ------------------------------------------------------------------

IIC3413DBParser::ConstantContext::ConstantContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* IIC3413DBParser::ConstantContext::INTEGER() {
  return getToken(IIC3413DBParser::INTEGER, 0);
}

tree::TerminalNode* IIC3413DBParser::ConstantContext::STRING() {
  return getToken(IIC3413DBParser::STRING, 0);
}


size_t IIC3413DBParser::ConstantContext::getRuleIndex() const {
  return IIC3413DBParser::RuleConstant;
}


std::any IIC3413DBParser::ConstantContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<IIC3413DBParserVisitor*>(visitor))
    return parserVisitor->visitConstant(this);
  else
    return visitor->visitChildren(this);
}

IIC3413DBParser::ConstantContext* IIC3413DBParser::constant() {
  ConstantContext *_localctx = _tracker.createInstance<ConstantContext>(_ctx, getState());
  enterRule(_localctx, 48, IIC3413DBParser::RuleConstant);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(206);
    _la = _input->LA(1);
    if (!(_la == IIC3413DBParser::INTEGER

    || _la == IIC3413DBParser::STRING)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- IdentifierContext ------------------------------------------------------------------

IIC3413DBParser::IdentifierContext::IdentifierContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* IIC3413DBParser::IdentifierContext::IDENTIFIER() {
  return getToken(IIC3413DBParser::IDENTIFIER, 0);
}

IIC3413DBParser::KeywordContext* IIC3413DBParser::IdentifierContext::keyword() {
  return getRuleContext<IIC3413DBParser::KeywordContext>(0);
}


size_t IIC3413DBParser::IdentifierContext::getRuleIndex() const {
  return IIC3413DBParser::RuleIdentifier;
}


std::any IIC3413DBParser::IdentifierContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<IIC3413DBParserVisitor*>(visitor))
    return parserVisitor->visitIdentifier(this);
  else
    return visitor->visitChildren(this);
}

IIC3413DBParser::IdentifierContext* IIC3413DBParser::identifier() {
  IdentifierContext *_localctx = _tracker.createInstance<IdentifierContext>(_ctx, getState());
  enterRule(_localctx, 50, IIC3413DBParser::RuleIdentifier);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(210);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case IIC3413DBParser::IDENTIFIER: {
        enterOuterAlt(_localctx, 1);
        setState(208);
        match(IIC3413DBParser::IDENTIFIER);
        break;
      }

      case IIC3413DBParser::AND:
      case IIC3413DBParser::AS:
      case IIC3413DBParser::BETWEEN:
      case IIC3413DBParser::CREATE:
      case IIC3413DBParser::DISTINCT:
      case IIC3413DBParser::FROM:
      case IIC3413DBParser::INSERT:
      case IIC3413DBParser::INTO:
      case IIC3413DBParser::INT:
      case IIC3413DBParser::LIKE:
      case IIC3413DBParser::LIMIT:
      case IIC3413DBParser::OR:
      case IIC3413DBParser::SELECT:
      case IIC3413DBParser::STR:
      case IIC3413DBParser::TABLE:
      case IIC3413DBParser::VALUES:
      case IIC3413DBParser::WHERE: {
        enterOuterAlt(_localctx, 2);
        setState(209);
        keyword();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- LimitStatementContext ------------------------------------------------------------------

IIC3413DBParser::LimitStatementContext::LimitStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* IIC3413DBParser::LimitStatementContext::LIMIT() {
  return getToken(IIC3413DBParser::LIMIT, 0);
}

tree::TerminalNode* IIC3413DBParser::LimitStatementContext::INTEGER() {
  return getToken(IIC3413DBParser::INTEGER, 0);
}


size_t IIC3413DBParser::LimitStatementContext::getRuleIndex() const {
  return IIC3413DBParser::RuleLimitStatement;
}


std::any IIC3413DBParser::LimitStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<IIC3413DBParserVisitor*>(visitor))
    return parserVisitor->visitLimitStatement(this);
  else
    return visitor->visitChildren(this);
}

IIC3413DBParser::LimitStatementContext* IIC3413DBParser::limitStatement() {
  LimitStatementContext *_localctx = _tracker.createInstance<LimitStatementContext>(_ctx, getState());
  enterRule(_localctx, 52, IIC3413DBParser::RuleLimitStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(212);
    match(IIC3413DBParser::LIMIT);
    setState(213);
    match(IIC3413DBParser::INTEGER);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- KeywordContext ------------------------------------------------------------------

IIC3413DBParser::KeywordContext::KeywordContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* IIC3413DBParser::KeywordContext::AND() {
  return getToken(IIC3413DBParser::AND, 0);
}

tree::TerminalNode* IIC3413DBParser::KeywordContext::AS() {
  return getToken(IIC3413DBParser::AS, 0);
}

tree::TerminalNode* IIC3413DBParser::KeywordContext::BETWEEN() {
  return getToken(IIC3413DBParser::BETWEEN, 0);
}

tree::TerminalNode* IIC3413DBParser::KeywordContext::CREATE() {
  return getToken(IIC3413DBParser::CREATE, 0);
}

tree::TerminalNode* IIC3413DBParser::KeywordContext::DISTINCT() {
  return getToken(IIC3413DBParser::DISTINCT, 0);
}

tree::TerminalNode* IIC3413DBParser::KeywordContext::FROM() {
  return getToken(IIC3413DBParser::FROM, 0);
}

tree::TerminalNode* IIC3413DBParser::KeywordContext::INSERT() {
  return getToken(IIC3413DBParser::INSERT, 0);
}

tree::TerminalNode* IIC3413DBParser::KeywordContext::INTO() {
  return getToken(IIC3413DBParser::INTO, 0);
}

tree::TerminalNode* IIC3413DBParser::KeywordContext::INT() {
  return getToken(IIC3413DBParser::INT, 0);
}

tree::TerminalNode* IIC3413DBParser::KeywordContext::LIKE() {
  return getToken(IIC3413DBParser::LIKE, 0);
}

tree::TerminalNode* IIC3413DBParser::KeywordContext::LIMIT() {
  return getToken(IIC3413DBParser::LIMIT, 0);
}

tree::TerminalNode* IIC3413DBParser::KeywordContext::OR() {
  return getToken(IIC3413DBParser::OR, 0);
}

tree::TerminalNode* IIC3413DBParser::KeywordContext::SELECT() {
  return getToken(IIC3413DBParser::SELECT, 0);
}

tree::TerminalNode* IIC3413DBParser::KeywordContext::STR() {
  return getToken(IIC3413DBParser::STR, 0);
}

tree::TerminalNode* IIC3413DBParser::KeywordContext::TABLE() {
  return getToken(IIC3413DBParser::TABLE, 0);
}

tree::TerminalNode* IIC3413DBParser::KeywordContext::VALUES() {
  return getToken(IIC3413DBParser::VALUES, 0);
}

tree::TerminalNode* IIC3413DBParser::KeywordContext::WHERE() {
  return getToken(IIC3413DBParser::WHERE, 0);
}


size_t IIC3413DBParser::KeywordContext::getRuleIndex() const {
  return IIC3413DBParser::RuleKeyword;
}


std::any IIC3413DBParser::KeywordContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<IIC3413DBParserVisitor*>(visitor))
    return parserVisitor->visitKeyword(this);
  else
    return visitor->visitChildren(this);
}

IIC3413DBParser::KeywordContext* IIC3413DBParser::keyword() {
  KeywordContext *_localctx = _tracker.createInstance<KeywordContext>(_ctx, getState());
  enterRule(_localctx, 54, IIC3413DBParser::RuleKeyword);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(215);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 262142) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

void IIC3413DBParser::initialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  iic3413dbparserParserInitialize();
#else
  ::antlr4::internal::call_once(iic3413dbparserParserOnceFlag, iic3413dbparserParserInitialize);
#endif
}
