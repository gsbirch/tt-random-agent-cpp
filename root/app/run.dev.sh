#!/bin/bash

# Development Execute

# Use the server's self-signed public key.
export SSL_CERT_FILE=/etc/tt/certs/tt-chain.pem

# Run the agent
./build/src/tt-random-agent