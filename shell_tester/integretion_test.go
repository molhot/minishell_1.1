package shell_tester

import (
    "os/exec"
    "os"
    "testing"
)

func TestMyShell(t *testing.T) {
    // テストケースを定義する
    tests := []struct {
        input  string
        output string
    }{
        {input: "echo Hello World\n"},
        {input: "/bin/echo HOGE\n"},
        {input: "echo 'aaa'\"aaa\"'\"AAA\"'\n"},
        {input: "echo $NONE aaa $NONE\n"},
        {input: "echo $NONE'aaa'$NONE\n"},
        {input: "echo $USER$$$'$USER'\"$USER\"\n", output: "testuser$$$USERtestuser\n"},
        {input: `echo "'"'''"'"''"'"'$"'"'"''"'""\n`},
        {input: `echo "$NONE""$NONE""$NONE"\n`},
        {input: `echo "$NONE"''"$NONE"''"$NONE"\n`},
        {input: `echo aaa '' aaa\n`},
        {input: `echo -naaaaa aaaaa -n aaaa\n`},
        {input: `echo -n aaa`},
        {input: `echo -n -n -n aaa`},
        {input: `echo -nn-n aaa`},
        {input: `echo -nnn aaa`},
        {input: `echo -nnn-- aaa`},
        {input: `echo - - - aaa`},
        {input: `echo $$`, output: "$$\n"},
        {input: `cat ""`},
    }

    // テスト用の環境変数の準備
    os.Setenv("USER", "testuser")
    // テストケースを実行する
    for _, tc := range tests {

        // minishellでコマンドを実行して、出力結果を取得する
        cmd := exec.Command("./minishell", "-c", tc.input)
        actualOutput, err := cmd.Output()
        if err != nil {
            t.Error("minishell command failed:", err)
        }

        // 期待される出力がテストケースに定義されている場合は、その出力を期待される結果とする
        expectedOutput := tc.output
        if expectedOutput == "" {
            // テストケースに出力が定義されていない場合は、Bashでコマンドを実行して得られる結果を期待される結果とする
            bashCmd := exec.Command("bash", "-c", tc.input)
            expectedOutputBytes, err := bashCmd.Output()
            if err != nil {
                t.Error("Bash command failed:", err)
            }
            expectedOutput = string(expectedOutputBytes)
        }

        // 出力結果を比較する
        if string(actualOutput) != string(expectedOutput) {
            t.Fatalf("expected %q but got %q", expectedOutput, actualOutput)
        }
    }
}

