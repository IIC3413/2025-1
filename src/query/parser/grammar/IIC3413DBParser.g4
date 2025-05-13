parser grammar IIC3413DBParser;

options {
    tokenVocab = IIC3413DBLexer;
}

root: query EOF;

query: createQuery | insertQuery | selectQuery;

createQuery: CREATE TABLE identifier '(' schema (',' schema)* ')';

insertQuery: INSERT INTO identifier VALUES '(' constant (',' constant)* ')';

selectQuery: selectStatement fromStatement whereStatement? limitStatement?;

schema: identifier datatype;

datatype: STR | INT;

selectStatement: SELECT DISTINCT? ('*' | columnList);

columnList: column (',' column)*;

fromStatement: FROM tableList;

tableList: tableListItem (',' tableListItem)*;

tableListItem: leftOuterJoin | table;

leftOuterJoin: '(' identifier LEFT OUTER JOIN identifier ON outerJoinOn')' AS identifier;

outerJoinOn: outerJoinComp (AND outerJoinComp)*;

outerJoinComp: column '==' column;

table: identifier (AS identifier)?;

whereStatement: WHERE andExpr;

andExpr: simpleExpr (AND simpleExpr)*;

simpleExpr: comparisonExpr
|           likeExpr
|           betweenExpr
;

comparisonExpr: columnOrConstant (op=('=='|'!='|'<'|'>'|'<='|'>=') columnOrConstant)?;

likeExpr: column LIKE STRING;

betweenExpr: column BETWEEN constant AND constant;

columnOrConstant: column | constant;

column: identifier ('.' identifier)?;

constant: INTEGER | STRING;

identifier: IDENTIFIER | keyword;

limitStatement: LIMIT INTEGER;

keyword: AND
|        AS
|        BETWEEN
|        CREATE
|        DISTINCT
|        FROM
|        INSERT
|        INTO
|        INT
|        LIKE
|        LIMIT
|        OR
|        SELECT
|        STR
|        TABLE
|        VALUES
|        WHERE
;
