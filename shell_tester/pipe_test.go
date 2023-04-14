package shell_tester

import (
	"bytes"
	"os/exec"
	"strings"
	"testing"
)

func TestPipe(t *testing.T) {
	testCases := []struct {
		name   string
		args   string
		output string
	}{
		{
			name:   "single pipe",
			args:   "echo hoge | sed s/hoge/fuga/",
			output: "fuga\n",
		},
		{
			name:   "multiple pipes",
			args:   "echo hoge | sed s/hoge/fuga/ | tr a-z A-Z",
			output: "FUGA\n",
		},
	}

	for _, tc := range testCases {
		t.Run(tc.name, func(t *testing.T) {
			shell := exec.Command("./minishell", "-c", tc.args)

			// Set up pipes for input and output
			stdin, err := shell.StdinPipe()
			if err != nil {
				t.Fatalf("unexpected error: %v", err)
			}
			defer stdin.Close()

			stdout := &bytes.Buffer{}
			shell.Stdout = stdout

			// Start shell
			err = shell.Start()
			if err != nil {
				t.Fatalf("unexpected error: %v", err)
			}

			// Write input to shell
			_, err = stdin.Write([]byte(tc.args))
			if err != nil {
				t.Fatalf("unexpected error: %v", err)
			}

			// Close input pipe and wait for shell to exit
			err = stdin.Close()
			if err != nil {
				t.Fatalf("unexpected error: %v", err)
			}
			err = shell.Wait()
			if err != nil {
				t.Fatalf("unexpected error: %v", err)
			}

			// Compare output to expected value
			if strings.TrimSpace(stdout.String()) != strings.TrimSpace(tc.output) {
				t.Errorf("unexpected output:\n\twant: %q\n\tgot: %q", tc.output, stdout.String())
			}
		})
	}
}

