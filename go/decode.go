package main

import (
	"bytes"
	"compress/zlib"
	"flag"
	"fmt"
	"os"
)

func main() {
	filename := flag.String("f", "", "Specify file to decode")
	flag.Parse()

	var file *os.File

	if filename != nil && *filename != "" {
		f, err := os.Open(*filename)
		if err != nil {
			fmt.Printf("Failed to open file(%s): %v", *filename, err)
			return
		}
		defer f.Close()

		file = f
	} else {
		file = os.Stdin
	}

	r, err := zlib.NewReader(file)
	if err != nil {
		fmt.Printf("Failed to create zlib reader")
	}
	defer r.Close()

	var buf bytes.Buffer
	buf.ReadFrom(r)

	fmt.Print(buf.String())
}
