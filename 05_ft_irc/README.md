# WALL-E IRC Server

> *This project has been created as part of the 42 curriculum by juagomez, jumarque, emcorona.*

## Description

WALL-E is a robust Internet Relay Chat (IRC) server implemented in C++ that enables real-time text communication between multiple users over TCP sockets. This server handles thousands of simultaneous connections using efficient I/O multiplexing with poll(), implementing the classic IRC protocol as defined in RFC 1459 and RFC 2812.

### Project Goals

- Implement a multi-client TCP server capable of handling numerous concurrent connections
- Parse and process IRC protocol commands (NICK, JOIN, PART, PRIVMSG, MODE, etc.)
- Manage virtual channels with modes (operator privileges, key passwords, user limits)
- Provide a chatbot with various commands for user interaction
- Learning about system programming concepts including sockets, select/poll, and system calls

### Architecture Overview

The server follows a layered architecture with Model-Controller-Server layers for separation of concerns and clean code organization.

## Instructions

### Compilation

Ensure you have a C++98-compatible compiler installed (c++). Then compile the project:

```bash
make
```

This will create the ircserv executable.

### Running the Server

Start the server by providing the port number and password:

```bash
./ircserv <port> <password>
```

**Example:**

```bash
./ircserv 6667 mysecret/
```

**Port Requirements:**
- Valid range: 1-65535
- Recommended range: 1024-49151 (registered ports)
- Avoid system ports (1-1023) and dynamic ports (49152-65535)

#Aquí tienes la traducción adaptada perfectamente para tu archivo Markdown:

## Connecting with an IRC Client

#### Using nc (netcat)
```bash
nc localhost 6667
PASS mypassword
NICK mynick
USER myuser 0 * :My Real Name
JOIN #general
PRIVMSG #general :Hello world!

```

#### Using HexChat

1. Add server: `localhost/6667`
2. Set server password: `mypassword`
3. Connect

### Make Commands

| Command | Description |
| --- | --- |
| `make` | Compiles the project |
| `make clean` | Removes object files |
| `make fclean` | Removes all generated files |
| `make re` | Full recompilation |


### Cleaning

```bash
make clean      # Remove object files
make fclean     # Remove objects and executable
```

## Usage Examples

### Client Commands Reference

| Command | Description | Example |
|---------|-----|----------|
| NICK <nickname> | Set your nickname | NICK jumarque |
| USER <user> <host> :<name> | Register user | USER guest 0 * :John Doe |
| JOIN #channel | Join a channel | JOIN #general |
| TOPIC #channel | View/change topic | TOPIC #general :Welcome |
| PART #channel | Leave channel | PART #general |
| PRIVMSG #channel :msg | Send message | PRIVMSG #general :Hello! |
| KICK #channel nick | Kick user (op only) | KICK #general Troll |
| MODE #channel +k key | Set channel key | MODE #general +k 1234 |
| MODE #channel +o nick | Give operator status | MODE #general +o Moderator |
| PING <token> | Keepalive check | PING 12345 |
| QUIT | Disconnect | QUIT :Goodbye |

### Bot Commands

Send these commands to the bot user (bot) for interactive features:

- !help - List available bot commands
- !time - Show current server time
- !channels - List all channels
- !joke - Get a random joke

**Example:**
```
PRIVMSG bot :!time
```

## Resources

### Documentation

- **RFC 1459**: Internet Relay Chat Protocol - Original specification
  - https://datatracker.ietf.org/doc/html/rfc1459
- **RFC 2812**: Internet Relay Chat - Protocol Specification
  - https://datatracker.ietf.org/doc/html/rfc2812
- **Linux poll(7)** - I/O multiplexing
  - https://man7.org/linux/man-pages/man2/poll.2.html
- **Linux socket(7)** - Socket programming interface
  - https://man7.org/linux/man-pages/man2/socket.2.html
- **Berkeley Sockets** - API documentation
  - https://en.cppreference.com/cpp/header

### Articles and Tutorials

- [IRC command](https://www.jcea.es/irc/cmd_irc.htm)
- [IRC Protocol Explained - Wikipedia](https://en.wikipedia.org/wiki/IRC)

### Technical References

- **Linux System Programming** by Robert Love
- **Unix Network Programming** by W. Richard Stevens
- [Network Programming with Cpp](https://www.dre.vanderbilt.edu/~schmidt/PDF/ACE-tutorial.pdf)

---

## AI Usage in This Project

**Note:** This project was developed primarily through traditional learning and manual coding practices.

**AI Tools Used:**
- Code analysis and review for potential issues
- Documentation generation and structure suggestions
- Code formatting and style consistency checking

**AI-Assisted Tasks:**
- README.md content generation and organization
- Command reference table formatting
- Architecture documentation and flow diagrams

**Core Implementation:**
- All core logic was implemented manually in C++98
- No AI-generated code was used in the main implementation
- Protocols and algorithms were researched through official RFCs
