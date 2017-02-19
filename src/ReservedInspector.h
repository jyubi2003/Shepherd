/*
 * 自動テストプログラム
 *
 * 逐次通知された文字を評価し、予約語かを評価するクラス
 *
 * クラス名: ReservedInspector
 *
 * 作成者: FJH
 * 作成日: 2016/7/12
 */

#if !defined(__RESERVED_INSPECTOR__)
#define __RESERVED_INSPECTOR__

#include "SourceAnalizer.h"
#include "ElementProperties.h"
#include "ElementRepository.h"
#include "InspectorBase.h"

#define RESERVED_TOKEN_NUM		32

typedef struct tag_ReservedKeyword{
	const char*		pKeyword;
	TokenKind		kind;
} st_ReservedKeyword;


class ReservedInspector : public InspectorBase{
protected:

	const char*		name ="ReservedInspector";

	//予約言吾一覧
	st_ReservedKeyword reservedTokens[RESERVED_TOKEN_NUM] = {
		{"import",		ImportKeyword		},
		{"define",		DefineKeyword		},
		{"if",			IfKeyword			},
		{"using",		UsingKeyword		},
		{"namespace",	NamespaceKeyword	},
		{"public",		PublicKeyword		},
		{"protected",	ProtectedKeyword	},
		{"private",		PrivateKeyword		},
		{"class",		ClassKeyword		},
		{"extends",		ExtendsKeyword		},
		{"implements",	ImplementsKeyword	},
		{"string",		StringKeyword		},
		{"get",			GetKeyword			},
		{"set",			SetKeyword			},
		{"return",		ReturnKeyword		},
		{"delegate",	DelegateKeyword		},
		{"void",		VoidKeyword			},
		{"object",		ObjectKeyword		},
		{"event",		EventKeyword		},
		{"virtual",		VirtualKeyword		},
		{"null",		NullKeyword			},
		{"this",		ThisKeyword			},
		{"new",			NewKeyword			},
		{"override",	OverrideKeyword		},
		{"base",		BaseKeyword			},
		{"boolean",		BooleanKeyword		},
		{"BOOL",		BoolKeyword			},
		{"int",			IntKeyword			},
		{"INTEGER",		IntegerKeyword		},
		{"float",		FloatKeyword		},
		{"FLOAT",		FLOATKeyword		},
		{"EOL",			EndOfListKeyword	}
	};

public:
	/* inspect		: 予約語評価
	 * 	inPutBuff	: 入力文字
	 * 	pRepo		: リボジトリ
	 *  pos			: 評価位置
	 * 人力文字を評価し、予約語の条件を満たすか判定する
	 *  return	:OK=1, NG=0
	 */
	int	inspect(char* inputBuff, ElementRepository* pRepo, int pos);

private:
	/* chkReserved:予約語評価
	 * 	バッファを評価し、予約語の条件を満たすか判定する
	 * 	return = 予約言吾 = 1, 予約語ではない = O
	 */
	int chkReserved(TokenKind&);

};	//EHD of Class

#endif	//__RESERVED_INSPECTOR__
