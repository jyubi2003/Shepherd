/*
＊BOSS業務APL調査用プログラム
＊
＊ ソース解析プログラムの共通ヘッダ
＊
＊プログラム名： SourceAnalizer．h
＊
＊作成者：FJH
＊作成日：2016/7/12
 */
 
#if !defined(__SourceAnalizer__)
#define __SourceAnalizer__

/*
 *定数一覧
 */

/*要素*/
#define START_IMPORT
#define END_IMPORT
#define START_IDENTIFIER
#define END_IDENTIFIER

/*論理値 */
#define OK 1
#define NG 0
#define true 1
#define false 0

/*構文解析用の定数群*/
/*各種長さ*/
#define	ANALIZE_BUFF_SIZE		2048
#define	IMPORT_REPO_SIZE		2048
#define	IMPORT_REPO_NUM			128
#define	IDENTIFIER_REPO_SIZE		128
#define	IDENTIFIER_REPO_NUM		65535
#define	INPUT_BUFF_SIZE			16
#define	INPUT_CHAR_NUM			1
#define	INPUT_MEMBER_NUM		1
#define	FUNC_NAME_SIZE			1024
#define	STACK_FUNC_SIZE			1024

#endif /*__SourceAnalizer__*/
