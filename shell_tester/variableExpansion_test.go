package shell_tester

import (
	"bytes"
	"os"
	"os/exec"
	"testing"
)

func TestVariableExpansion(t *testing.T) {
	cmd := "./minishell"
	tests := []struct {
		name     string
		command  string
		expected string
	}{
		{
			name:     "Expand single variable",
			command:  "echo $FOO",
			expected: "bar\n",
		},
		{
			name:     "Expand multiple variables",
			command:  "echo $FOO$BAR",
			expected: "barbaz\n",
		},
		{
			name:     "Expand variable with whitespace",
			command:  "echo $FOO $BAR",
			expected: "bar baz\n",
		},
		{
			name:     "Expand variable in quotes",
			command:  "echo \"$FOO\"",
			expected: "bar\n",
		},
		{
			name:     "Expand variable in double quotes",
			command:  "echo \"$FOO $BAR\"",
			expected: "bar baz\n",
		},
		{
			name:     "Expand undefined variable",
			command:  "echo $UNDEFINED",
			expected: "\n",
		},
	}

	for _, test := range tests {
		t.Run(test.name, func(t *testing.T) {
			var stdout bytes.Buffer
			var stderr bytes.Buffer
			env := os.Environ()
			env = append(env, "FOO=bar", "BAR=baz")
			cmd := exec.Command(cmd, "-c", test.command)
			cmd.Env = env
			cmd.Stdout = &stdout
			cmd.Stderr = &stderr
			err := cmd.Run()
			if err != nil {
				t.Fatalf("command %q failed: %v", test.command, err)
			}
			actual := stdout.String()
			if actual != test.expected {
				t.Fatalf("unexpected output: expected=%q, actual=%q", test.expected, actual)
			}
		})
	}
}

