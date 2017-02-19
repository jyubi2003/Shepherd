/*
 * 自動ﾃｽﾄ検証ﾌﾟﾛｸﾞﾗﾑ
 *
 * 要素のクラス、タイプ、種別
 *
 * クラス名: ElernentProperties
 * ファイル名: ElementProperties.h
 *
 * 作成者: FJH
 * 作成日: 2016/7/12
 */
#if !defined(__ELEMENT_PROPERTIES__)
#define __ELEMENT_PROPERTIES__

#define ELEMENT_CLASS_NUM	4
#define NODE_TYPE_NUM		37
#define NODE_KIND_NUM		39
#define TOKEN_TYPE_NUM		2
#define TOKEN_KIND_NUM		94
#define TORIVIA_TYPE_NUM	2
#define TORIVIA_KIND_NUM	3

/*
 *要素のクラス（ノード、トークン、トリビア）
 */
enum ElementClass { NoneElementClass,
					Node,
					Token,
					Torivia
};

/*
 *要素がノードの場合のタイプ
 */
enum NodeType {	NoneNodeType,
				CompilationUnitSyntax,
				UsingDirectiveSyntax, 			// for C#
				ImportDirectiveSyntax, 			// for Java
				IdentifierNameSyntax,
				QualifiedNameSyntax,
				NamespaceDecIarationSyntax,
				ClassDeclarationSyntax,
				BaseListSyntax,
				SimpleBaseTypeSyntax,
				FieldDeclarationSyntax,
				VariableDeclarationSyntax,
				PredefinedTypeSyntax,
				PropertyDeclarationSyntax,
				AccessorListSyntax,				// for C#
				AccessorDeclarationSyntax,		// for C#
				BlockSyntax,
				ReturnStatementSyntax,
				ExpressionStatementSyntax,
				AssignmentExpressionSyntax,
				DelegateDeclarationSyntax,		// for C#
				ParameterListSyntax,
				ParameterSyntax,
				EventFieldDecJaratjonSyntax,	// for C#
				MethodDecIarationSyntax,
				IfStatementSyntax,
				BinaryExpressionSyntax,
				LiteralExpressionSyntax,
				InvocationExpressionSyntax,
				ArgumentListSyntax,
				ArgumentSyntax,
				ThisExpressionSyntax,
				ConstructorDeclarationSyntax,
				ObjectCreationExpressionSyntax,
				MemberAccessExpressionSyntax,
				BaseExpressjonSyntax,			// for C#
				BracketedArgumentListSyntax		// for C#
};

/*
 * 要素がノードの場合の種別
 */
enum NodeKind {	NoneNodeKind,
				CompilationUnit,
				UsingDirective,					// for C#
				ImportDirective,				// for Java
				IdentifierName,
				QualifiedName,
				NamespaceDeclaration,
				ClassDeclaration,
				BaseList,
				SimpleBaseType,
				FieldDeclaration,
				VariableDeclaration,
				PredefinedType,
				PropertyDeclaration,
				AccessorList,					// for C#
				GetAccessorDeclaration,			// for C#
				SetAccessorDeclaration,			// for C#
				Block,
				ReturnStatement,
				ExpressionStatement,
				SimpleAssignmentExpression,
				DelegateDecraration,			// for C#
				ParameterList,
				Parameter,
				EventFieldDeclaration,			// for C#
				MethodDeclaration,
				IfStatement,
				NotEqualsExpression,
				NullLiteralExpression,
				InvocationExpression,
				ArgumentList,
				Argument,
				ThisExpression,
				ConstructorDeclaration,
				ObjectCreationExpression,
				StringLiteralExpression,
				SimpleMemberAccessExpression,
				BaseExpression,					// for C#
				BracketedArgumentList			// for C#
};

/*
 * 要素がトークンの場合のタイプ
 */
enum TokenType {	NoneTokenType,
					SyntaxToken
};

/*
 * 要素がトークンの場合の種別
 */
enum TokenKind {	NoneTokenKind,									// 00 (Ox00)
					ImportKeyword,									// 01 (Ox01)
					DefineKeyword,									// 02 (Ox02)
					UsingKeyword,									// 03 (Ox03)
					IdentifierToken,								// 04 (Ox04)
					SemicolonToken,									// 05 (Ox05)
					ColonToken,										// 06 (Ox06)
					DotToken,										// 07 (Ox07)
					CommaToken,										// 08 (Ox08)
					NamespaceKeyword,								// 09 (Ox09)
					OpenBracketToken,								// 10 (Ox0a)
					CloseBracketToken,								// 11 (Ox0b)
					OpenBraceToken,									// 12 (Ox0c)
					CloseBraceToken,								// 13 (Ox0d)
					OpenParenToken,									// 14 (Ox0e)
					CloseParenToken,								// 15 (Ox1f)
					PublicKeyword,									// 16 (Ox10)
					ProtectedKeyword,								// 17 (Ox11)
					PrivateKeyword,									// 18 (Ox12)
					ClassKeyword, 									// 19 (Ox13)
					StringKeyword, 									// 20 (Ox14)
					GetKeyword, 									// 21 (Ox15) for C#
					SetKeyword, 									// 22 (Ox16) for C#
					ReturnKeyword, 									// 23 (Ox17)
					EqualsToken, 									// 24 (Ox18)
					DelegateKeyword, 								// 25 (Ox19) for C#
					VoidKeyword, 									// 26 (Oxla)
					BooleanKeyword, 								// 27 (Oxlb)
					BoolKeyword, 									// 28 (OxIc)
					IntKeyword, 									// 29 (Oxld)
					IntegerKeyword, 								// 30 (Oxle)
					FloatKeyword, 									// 31 (Oxlf)
					FLOATKeyword, 									// 32 (Ox20)
					ObjectKeyword, 									// 33 (Ox21)
					EventKeyword, 									// 34 (Ox22) for C#
					VirtualKeyword, 								// 35 (Ox23)
					IfKeyword, 										// 36 (Ox24)
					ExclamationEqualsToken, 						// 37 (Ox25)
					NullKeyword, 									// 38 (Ox26)
					ThisKeyword, 									// 39 (Ox27)
					NewKeyword, 									// 40 (Ox28)
					OverrideKeyword, 								// 41 (Ox29)
					StringLiteralToken, 							// 42 (Ox2a)
					BaseKeyword, 									// 43 (Ox2b) for C#
					EndOfFileToken, 								// 44 (Ox2c) EOF virtualtoken
					CStyleCommentToken, 							// 45 (Ox2d)
					CppStyleCommentToken, 							// 46 (Ox2e)
					AbstructKeyword, 								// 47 (Ox30) Class Modifier
					StaticKeyword, 									// 48 (Ox31) Class Modifier
					FinalKeyword, 									// 49 (Ox32) Class Modifier
					StrictFpKeyword, 								// 50 (Ox33) Class Modifier
					ExtendsKeyword, 								// 51 (Ox34)
					ImplementsKeyword, 								// 52 (Ox35)
					SingleQuortToken, 								// 53 (Ox36)
					DoubleQuortToken, 								// 54 (Ox37)
					AssignmentEqualOperator,						// 55 (0x38)
					NumericalComparisonGraterThanOperator,			// 56 (0x39)
					NumericalComparisonLessThanOperator,			// 57 (0x3a)
					NotOperator,									// 58 (Ox3b)
					BitwiseComplementOperator,						// 59 (Ox3c)
					LambdaExpressionOperator,						// 60 (Ox3d)
					ConditionalAndOperator,							// 61 (Ox3e)
					ConditionalOrOperator,							// 62 (Ox3f)
					EqualToOperator,								// 63 (Ox40)
					NumericalComparisonGraterThanEqualOperator,		// 64 (Ox41)
					NumericalComparisonLessThanEqualOperator,		// 65 (Ox42)
					NotEqualToOperator,								// 66 (Ox43)
					IncrementOperator,								// 67 (Ox44)
					DecrementOperator,								// 68 (Ox45)
					PlusOperator,									// 69 (Ox46)
					MinusOperator,									// 70 (Ox47)
					MultipleOperator,								// 71 (Ox48)
					DevideOperator,									// 72 (Ox49)
					BitwiseLogicalAndOperator,						// 73 (Ox4a)
					InclusiveOrOperator,							// 74 (Ox4b)
					ExclusiveOrOperator,							// 75 (Ox4c)
					ModulusOperator,								// 76 (Ox4d)
					ShiftLeftOperator,								// 77 (Ox4e)
					SignedRightShiftOperator,						// 78 (Ox4f)
					UnsignedRightShiftOperator,						// 79 (Ox50)
					CompoundAssignmentPlusOperator,					// 80 (Ox51)
					CompoundAssignmentMinusOperator,				// 81 (Ox52)
					CompoundAssignmentMultipleOperator,				// 82 (Ox53)
					CompoundAssignmentDevideOperator,				// 83 (Ox54)
					CompoundAssignmentLogicalAndOperator,			// 84 (Ox55)
					CompoundAssignmentInclusiveOrOperator,			// 85 (Ox56)
					CompoundAssignmentExclusiveOrOperator,			// 86 (Ox57)
					CompoundAssignmentModulusOperator,				// 87 (Ox58)
					CompoundAssignmentLeftShiftOperator,			// 88 (Ox59)
					CompoundAssignmentSignedRightShiftOperator,		// 89 (Ox5a)
					CompoundAssignmentUnsignedRightShiftOperator,	// 90 (Ox5b)
					ConditionalOperator, 							// 91 (Ox5c)
					InstanceofOperator, 							// 92 (Ox5d)
					EndOfListKeyword, 								// 93 (Ox5e) End Of This List
};

/*
 * 要素がトリビアの場合のタイプ
 */
enum ToriviaType{	NoneToriviaType,
					SyntaxTrivia
};

/*
 * 要素がトリビアの場合の種別
 */
enum ToriviaKind{	NoneToriviaKind,
					EndOfLineTrivia,
					WhitespaceTrivia
};

/*
 * 要素のクラス毎のタイプ／種別と共用体
 */
typedef struct tag_Node{
	NodeType		nodeType;
	NodeKind		nodeKind;
} st_Node;

typedef struct tag_Token{
	TokenType		tokenType;
	TokenKind		tokenKind;
} st_Token;

typedef struct tag_Torivia{
	ToriviaType		toriviaType;
	ToriviaKind		toriviaKind;
} st_Torivia;

typedef union tag_TypeKind{
	st_Node 		node;
	st_Token 		token;
	st_Torivia 		torivia;
} un_TypeKind;

/*
 * Elementクラスのタイプ、種別を管理するクラス
 */
class ElementProperties {
protected:
	/*
	 * 要素のクラス（ノード、トークン、トリビア）
	 */
	const char* lt_ElementClass[ELEMENT_CLASS_NUM] = {
		"NoneElementClass",
		"Node",
		"Token",
		"Torivia"
	};

	/*
	 * 要素がノードの場合のタイプ
	 */
	const char* lt_NodeType[NODE_TYPE_NUM] = {
		"NoneNodeType",
		"CompilationUnitSyntax",
		"UsingDirectiveSyntax",
		"ImportDirectiveSyntax",
		"ldentifierNameSyntax",
		"QualifiedNameSyntax",
		"NamespaceDeclarationSyntax",
		"ClassDeclarationSyntax",
		"BaseListSyntax",
		"SimpleBaseTypeSyntax",
		"FieldDeclarationSyntax",
		"VariableDeclarationSyntax",
		"PredefinedTypeSyntax",
		"PropertyDeclarationSyntax",
		"AccessorListSyntax",				// for C#
		"AccessorDeclarationSyntax",		// for C#
		"BlockSyntax",
		"ReturnStatementSyntax",
		"ExpressionStatementSyntax",
		"AssignmentExpressionSyntax",
		"DelegateDeclarationSyntax",		// for C#
		"ParameterListSyntax",
		"ParameterSyntax",
		"EventFieldDeclarationSyntax",		// for C#
		"MethodDeclarationSyntax",
		"IfStatementSyntax",
		"BinaryExpressionSyntax",
		"LiteralExpressionSyntax",
		"InvocationExpressionSyntax",
		"ArgumentListSyntax",
		"ArgumentSyntax",
		"ThisExpressionSyntax",
		"ConstructorDeclarationSyntax",
		"ObjectCreationExpressionSyntax",
		"MemberAccessExpressionSyntax",
		"BaseExpressionSyntax",				// for C#
		"BracketedArgumentListSyntax"		// for C#
	};

	/*
	 *要素がノードの場合の種別
	 */
	const char* lt_NodeKind[NODE_KIND_NUM] = {
		"NoneNodeKind",
		"CompilationUnit",
		"UsingDirective",
		"ImportDirective",
		"IdentifierName",
		"QualifiedName",
		"NamespaceDecIaration",
		"ClassDeclaration",
		"BaseList",
		"SimpleBaseType",
		"FieldDeclaration",
		"VariableDeclaration",
		"PredefinedType",
		"PropertyDeclaration",
		"AccessorList",						// for C#
		"GetAccessorDeclaration",			// for C#
		"SetAccessorDeclaration",			// for C#
		"Block",
		"ReturnStatement",
		"ExpressionStatement",
		"SimpleAssignmentExpression",
		"DelegateDeclaration",				// for C#
		"ParameterList",
		"Parameter",
		"EventFieIdDeclaration",			// for C#
		"MethodDeclaration",
		"IfStatement",
		"NotEquaIsExpression",
		"NullLiteralExpression",
		"InvocationExpression",
		"ArgumentList",
		"Argument",
		"ThisExpression",
		"ConstructorDeclaration",
		"ObjectCreationExpression",
		"StringLiteratExpression",
		"SimpleMemberAccessExpression",
		"BaseExpression",					// for C#
		"BracketedArgumentList"				// for C#
	};

	/*
	 * 要素がトークンの場合のタイプ
	 */
	const char* lt_TokenType[TOKEN_TYPE_NUM] = {
		"NoneTokenType",
		"SyntaxToken"
	};

	/*
	 * 要素がトークンの場合の種別
	 */
	const char* lt_TokenKind[TOKEN_KIND_NUM] = {
		"NoneTokenKind", 								//  0 (OxO)
		"ImportKeyword", 								//  1 (Oxl)
		"DefineKeywoerd",								//  2 (Ox2)
		"UsingKeyword",									//  3 (Ox3)
		"IdentifierToken",								//  4 (Ox4)
		"SemicolonToken",								//  5 (Ox5)
		"CoronToken",									//  6 (Ox6)
		"DotToken",										//  7 (Ox7)
		"CommaToken",									//  8 (Ox8)
		"NamespaceKeyword",								//  9 (Ox9)
		"OpenBracketToken",								// 10 (Oxa)
		"CloseBracketToken",							// 11 (Oxb)
		"OpenBraceToken",								// 12 (Oxc)
		"CloseBraceToken",								// 13 (Oxd)
		"OpenParenToken",								// 14 (Oxe)
		"CloseParenToken",								// 15 (Oxf)
		"PublicKeyword",								// 16 (Ox10)
		"ProtectedKeyword",								// 17 (Ox11)
		"PrivateKeyword",								// 18 (Ox12)
		"ClassKeyword",									// 19 (Ox13)
		"StringKeyword",								// 20 (Ox14)
		"GetKeyword",									// 21 (Ox15)
		"SetKeyword",									// 22 (Ox16)
		"ReturnKeyword",								// 23 (Ox17)
		"EqualsToken",									// 24 (Ox18)
		"DelegateKeyword",								// 25 (Ox19) //forC#
		"VoidKeyword",									// 26 (Ox1a) //forC#
		"BooleanKeyword",								// 27 (Ox1b) //forC#
		"BoolKeyword",									// 28 (OxIc)
		"IntKeyword", 									// 29 (Oxld)
		"IntegerKeyword", 								// 30 (Oxle)
		"FloatKeyword",									// 31 (Oxlf)
		"FLOATKeyword",									// 32 (Ox20)
		"ObjectKeyword",								// 33 (Ox21)
		"EventKeyword",									// 34 (Ox22)
		"VirtualKeyword",								// 35 (Ox23)
		"IfKeyword",									// 36 (Ox24)
		"ExclamationEqualsToken",						// 37 (0x25)
		"NullKeyword",									// 38 (0x26)
		"ThisKeyword",									// 39 (0x27)
		"NewKeyword",									// 40 (0x28)
		"OverrideKeyword",								// 41 (0x29)
		"StringLiteralToken",							// 42 (Ox2a)
		"BaseKeyword",									// 43 (Ox2b)
		"EndOfFileToken",								// 44 (Ox2c)
		"CStyleCommentToken",							// 45 (Ox2d)
		"CppStyleCommentToken",							// 46 (Ox2e)
		"AbstructKeyword",								// 47 (Ox2f)
		"StaticKeyword",								// 48 (Ox30) Class Modifier
		"FinalKeyword",									// 49 (Ox31) Class Modifier
		"StrictKeyword",								// 50 (Ox32) Class Modifier
		"ExtendsKeyword",								// 51 (Ox33) Class Modifier
		"ImplementsKeyword",							// 52 (Ox34) Class Modifier
		"SingleQuortToken",								// 53 (Ox35) Class Modifier
		"DoubleQuortToken",								// 54 (Ox36)
		"AssignmentEqualOperator",						// 55 (Ox37)
		"NumericalComparisonGraterThanOperator",		// 56 (Ox38)
		"NumericalComparisonLessThanOperator",			// 57 (Ox39)
		"NotOperator",									// 58 (Ox3a)
		"BitwidthComprisonOperator",					// 59 (Ox3b)
		"LambdaExpressionOperator",						// 60 (Ox3c)
		"ConditionalAndOperator",						// 61 (Ox3d)
		"ConditionalOrOperator",						// 62 (Ox3e)
		"EqualToOperator",								// 63 (Ox3f)
		"NumericalComparisonGraterThanEqualOperator",	// 64 (Ox40)
		"NumericalComparisonLessThanEqualOperator",		// 65 (Ox41)
		"NotEqualToOperator",							// 66 (Ox42)
		"IncrementOperator",							// 67 (Ox43)
		"DecrementOperator",							// 68 (Ox44)
		"PlusOperator",									// 69 (Ox45)
		"MinusOperator",								// 70 (Ox46)
		"MultipleOperator",								// 71 (Ox47)
		"DevideOperator",								// 72 (Ox48)
		"BitwidthLogicalAndOperator",					// 73 (Ox49)
		"InclusiveOrOperator",							// 74 (Ox4a)
		"ExclusiveOrOperator",							// 75 (Ox4b)
		"ModulusOperator",								// 76 (Ox4c)
		"ShiftLeftOperator",							// 77 (Ox4d)
		"SignedRightShiftOperator",						// 78 (Ox4e)
		"UnsignedRightShiftOperator",					// 79 (Ox4f)
		"CompoundAssignmentPlusOperator",				// 80 (Ox50)
		"CompoundAssignmentMinusOperator",				// 81 (Ox51)
		"CompoundAssignmentMultipleOperator",			// 82 (Ox52)
		"CompoundAssignmentDevideOperator",				// 83 (Ox53)
		"CompoundAssignmentLogicalAndOr",				// 84 (Ox54)
		"CompoundAssignmentInclusiveOr",				// 85 (Ox55)
		"CompoundAssignmentExclusiveOr",				// 86 (Ox56)
		"CompoundAssignmentModulusOperator",			// 87 (Ox57)
		"CompoundAssignmentLeftShiftOperator",			// 88 (Ox58)
		"CompoundAssignmentSignedRightShiftOperator",	// 89 (Ox59)
		"CompoundAssignmentUnsignedRightShiftOperator",	// 90 (Ox5a)
		"ConditionalOperator",							// 91 (Ox5b)
		"InstanceOfOperator",							// 92 (Ox5c)
		"EndOfLineKeyword"								// 93 (Ox5d) End Of This List
	};

	/*
	 * 要素がトリビアの場合のタイプ
	 */
	const char* lt_ToriviaType[TORIVIA_TYPE_NUM] = {
		"NoneToriviaType",
		"SyntaxTrivia"
	};

	/*
	 * 要素がトリビアの場合の種別
	 */
	const char* lt_ToriviaKind[TORIVIA_KIND_NUM] = {
		"NoneToriviaKind",
		"EndOfLineTrivia",
		"WhitespaceTrivia"
	};

public:
	/*
	 * 要素クラスの外部表現を返す
	 */
	const char* getElementClassString(ElementClass elemClass);

	/*
	 * 要素クラスに応じた、タイプの外部表現を返す
	 */
	const char* getTypeString(ElementClass elemClass, un_TypeKind typeKind);

	/*
	 * 要素クラスに応じた、種別の外部表現を返す
	 */
	const char* getKindString(ElementClass elemClass, un_TypeKind typeKind);
};
#endif	//__ELEMENT_PROPERTIES__
