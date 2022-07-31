/*

//@@@@@ ODBC 용클래스 //@@@@@

#include <windows.h>

#include <sqlext.h>

#include <stdio.h>


class PODBC {

    SQLHENV henv;

    SQLHDBC hdbc;

    SQLHSTMT hstmt;

    SQLRETURN retcode;

    // For specific error

    SQLSMALLINT length;

    SQLINTEGER rec = 0, native;

    SQLCHAR state[7], message[256];

public:

    void AllocateHandles();

    void ConnectDataSource();

    void ExecuteStatementDirect(SQLCHAR* sql);

    void PrepareStatement(SQLCHAR* sql);

    void ExecuteStatement();

    void RetrieveResult();

    void DisconnectDataSource();

};

int main()
{
    PODBC podbc;


    podbc.AllocateHandles();

    podbc.ConnectDataSource();

    podbc.ExecuteStatementDirect((SQLCHAR*)"SELECT * FROM TB_PATIENT_INFO");

    podbc.RetrieveResult();

    podbc.DisconnectDataSource();

    return 0;
}

//@@@@@ DBMS 연결 //@@@@@

void PODBC::AllocateHandles() {

    // 환경 핸들러 할당

    retcode = SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &henv);


    if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) {

        // ODBC 드라이버 버전 명시

        retcode = SQLSetEnvAttr(henv, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, 0);


        if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) {

            // 연결 핸들러 할당

            retcode = SQLAllocHandle(SQL_HANDLE_DBC, henv, &hdbc);


            if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) {

                printf("Allocate Success\n");

            }

            else {

                SQLGetDiagRec(SQL_HANDLE_DBC, hdbc, ++rec, state, &native, message, sizeof(message), &length);

                printf("%s : %ld : %ld : %s\n", state, rec, native, message);

            }

        }

        else {

            SQLGetDiagRec(SQL_HANDLE_ENV, henv, ++rec, state, &native, message, sizeof(message), &length);

            printf("%s : %ld : %ld : %s\n", state, rec, native, message);

        }

    }

    else {

        SQLGetDiagRec(SQL_HANDLE_ENV, henv, rec, state, &native, message, sizeof(message), &length);

        printf("%s : %ld : %ld : %s\n", state, rec, native, message);

    }

}

void PODBC::ConnectDataSource() {

    // 32-bit, 64-bit 주의

    retcode = SQLConnect(hdbc, (SQLCHAR*)"DSN", SQL_NTS, (SQLCHAR*)"사용자_이름", SQL_NTS, (SQLCHAR*)"비밀번호", SQL_NTS);

}

void PODBC::ExecuteStatementDirect(SQLCHAR* sql) {

    if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) {

        retcode = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt);

        printf("Connect Success\n");

    }

    else {

        SQLGetDiagRec(SQL_HANDLE_DBC, hdbc, ++rec, state, &native, message, sizeof(message), &length);

        printf("%s : %ld : %ld : %s\n", state, rec, native, message);

    }


    retcode = SQLExecDirect(hstmt, sql, SQL_NTS);


    if (retcode == SQL_SUCCESS) {

        printf("Query Seuccess\n");

    }

    else {

        SQLGetDiagRec(SQL_HANDLE_STMT, hstmt, ++rec, state, &native, message, sizeof(message), &length);

        printf("%s : %ld : %ld : %s\n", state, rec, native, message);

    }

}

void PODBC::PrepareStatement(SQLCHAR* sql) {

    if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) {

        retcode = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt);

        printf("Connect Success\n");

    }

    else {

        SQLGetDiagRec(SQL_HANDLE_DBC, hdbc, ++rec, state, &native, message, sizeof(message), &length);

        printf("%s : %ld : %ld : %s\n", state, rec, native, message);

    }


    retcode = SQLPrepare(hstmt, sql, SQL_NTS);


    if (retcode == SQL_SUCCESS) {

        printf("\nQuery Prepare Success\n");

    }

    else {

        SQLGetDiagRec(SQL_HANDLE_STMT, hstmt, ++rec, state, &native, message, sizeof(message), &length);

        printf("\n%s : %ld : %ld : %s\n", state, rec, native, message);

    }

}

void PODBC::ExecuteStatement() {

    retcode = SQLExecute(hstmt);


    if (retcode == SQL_SUCCESS) {

        printf("Query Execute Success\n");

    }

    else {

        SQLGetDiagRec(SQL_HANDLE_STMT, hstmt, ++rec, state, &native, message, sizeof(message), &length);

TB_PATIENT_INFO_name        printf("%s : %ld : %ld : %s\n", state, rec, native, message);

    }

}

void PODBC::RetrieveResult() {

    short pnt_uid;

    // char TB_PATIENT_INFO_name[16];

    float resi_no;

    SQLLEN cid, cna, cal;


    SQLBindCol(hstmt, 1, SQL_C_SHORT, &pnt_uid, sizeof(pnt_uid), &cid);

    //SQLBindCol(hstmt, 2, SQL_C_CHAR, &TB_PATIENT_INFO_name, sizeof(TB_PATIENT_INFO_name), &cna);

    SQLBindCol(hstmt, 3, SQL_C_FLOAT, &resi_no, sizeof(resi_no), &cal);


    printf("id\tname\t\tcal\t\tstars");


    do {

        retcode = SQLFetch(hstmt);

        //printf("\n%d\t%s\t%f", pnt_uid, TB_PATIENT_INFO_name, resi_no);
        printf("\n%d\t%f", pnt_uid, resi_no);
    } while (retcode != SQL_NO_DATA);


    SQLFreeStmt(hstmt, SQL_UNBIND);

}

void PODBC::DisconnectDataSource() {

    if (hstmt) {

        SQLFreeHandle(SQL_HANDLE_STMT, hstmt);

        hstmt = NULL;

    }



    SQLDisconnect(hdbc);



    if (hdbc) {

        SQLFreeHandle(SQL_HANDLE_DBC, hdbc);

        hdbc = NULL;

    }

    if (henv) {

        SQLFreeHandle(SQL_HANDLE_ENV, henv);

        henv = NULL;

    }

}
*/


