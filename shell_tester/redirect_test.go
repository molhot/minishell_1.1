package shell_tester

import (
	"bytes"
	"io/ioutil"
	"os"
	"os/exec"
	"strings"
	"testing"
)

func TestRedirect(t *testing.T) {
	testCases := []struct {
		name   string
		args   string
		output string
	}{
		{
			name:   "redirect stdout to file",
			args:   "echo hello > out.txt",
			output: "",
		},
		{
			name:   "redirect stdin from file",
			args:   "cat < in.txt",
			output: "hello\n",
		},
		{
			name:   "append to file",
			args:   "echo world >> out.txt",
			output: "",
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

			stderr := &bytes.Buffer{}
			shell.Stderr = stderr

			// Start shell
			err = shell.Start()
			if err != nil {
				t.Fatalf("unexpected error: %v", err)
			}

			// Write input to shell
			if strings.Contains(tc.args, "<") {
				inputFile, err := os.Open("in.txt")
				if err != nil {
					t.Fatalf("unexpected error: %v", err)
				}
				defer inputFile.Close()
				_, err = ioutil.ReadAll(inputFile)
				if err != nil {
					t.Fatalf("unexpected error: %v", err)
				}
			} else {
				_, err = stdin.Write([]byte(tc.args))
				if err != nil {
					t.Fatalf("unexpected error: %v", err)
				}
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
				t.Errorf("unexpected stdout:\n\twant: %q\n\tgot: %q", tc.output, stdout.String())
			}

			// Compare stderr to expected value
			if strings.TrimSpace(stderr.String()) != "" {
				t.Errorf("unexpected stderr:\n\twant: %q\n\tgot: %q", "", stderr.String())
			}
		})
	}
}
