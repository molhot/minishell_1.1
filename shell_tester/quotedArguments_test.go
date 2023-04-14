package shell_tester

import (
  "os/exec"
  "os"
  "testing"
)

func TestQuoting(t *testing.T) {
	testCases := []struct {
		name   string
		args   string
		output string
	}{
		{
			name:   "unquoted with spaces",
			args:   "echo hoge test",
			output: "hoge test\n",
		},
		{
			name:   "double quote with spaces",
			args:   "echo \"hoge test\"",
			output: "hoge test\n",
		},
		{
			name:   "double quote with escaped double quote",
			args:   "echo \"\\\"test\"",
			output: "\"test\n",
		},
		{
			name:   "double quote with escaped variable",
			args:   "echo \"\\$USER\"",
			output: "$USER\n",
		},
		{
			name:   "double quote with variable expansion",
			args:   "echo \"$USER test\"",
			output: "testuser test\n",
		},
		{
			name:   "double quote with escaped backslash",
			args:   "echo \"\\\\\"",
			output: "\\\n",
		},
		{
			name:   "single quote",
			args:   "echo 'hoge test'",
			output: "hoge test\n",
		},
  }

  os.Setenv("USER", "testuser")

	for _, tc := range testCases {
		t.Run(tc.name, func(t *testing.T) {
			out, err := exec.Command("./minishell", "-c", tc.args).Output()
			if err != nil {
				t.Fatalf("unexpected error: %v", err)
			}

			if string(out) != tc.output {
				t.Errorf("unexpected output:\n\twant: %q\n\tgot: %q", tc.output, out)
			}
		})
	}
}

