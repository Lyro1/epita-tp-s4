# define _GNU_SOURCE
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <sys/types.h>
# include <sys/socket.h>
# include <netdb.h>
# include <err.h>
# include <unistd.h>


char* build_query(const char *url, size_t *len)
{
    char* res;
    int locres = asprintf(&res, "%s%s%s", "GET ", url, " HTTP/1.0\n\r\n\r");
    if (locres < 0)
    {
        return NULL;
    }
    *len = locres;
    return res;
}

void get_page(const char *name, const char *url, const char *port)
{
    struct addrinfo hints;
    struct addrinfo *result, *rp;
    int addrinfo_error;

    // We setup an IPV4 and TCP connection
    memset(&hints, 0, sizeof (struct addrinfo));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = 0;
    hints.ai_protocol = 0;
 
    // name and port are strings (domaine name and port, obviously)
    // result will contain the result
    addrinfo_error = getaddrinfo(name, port, &hints, &result);
 
    // Error management
    if ( addrinfo_error != 0 ) {
        errx(EXIT_FAILURE, "Fail getting address for %s on port %s: %s",
	    name, port, gai_strerror(addrinfo_error));
    }
    
    // Search for a connection
    int cnx = -1;
    for (rp = result; rp != NULL; rp = rp->ai_next) {
        cnx = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);
        if (cnx == -1) continue;
        if ( connect(cnx, rp->ai_addr, rp->ai_addrlen) != -1 ) break;
        close(cnx);
    }

    // Free the result list since we don't need it anymore
    free(result);

    // Setup the query and send it throught the socket
    size_t querylen = 0;
    char *query = build_query(url, &querylen);
    if (querylen != 0 && cnx != -1)
    {
        write(cnx, query, querylen);
    }

    // Create the buffer and print the response to it
    char buffer[2048];
    while (read(cnx, buffer, 2047) != 0)
    {
        fprintf(stdout, "%s", buffer);
        bzero(buffer, 2048);
    }

    close(cnx);
}

int main()
{
    get_page("perdu.com", "http://perdu.com", "80");
    return 0;
}
