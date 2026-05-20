/*
 * EJERCICIO: ARGO (JSON Parser)
 * 
 * DESCRIPCIÓN:
 * Implementar un parser de JSON que construya un AST (Abstract Syntax Tree)
 * y pueda serializar de vuelta a formato JSON.
 * 
 * CONCEPTOS CLAVE:
 * 1. PARSING: Análisis sintáctico de texto estructurado
 * 2. AST: Representación en árbol del código/datos
 * 3. RECURSIVE DESCENT: Técnica de parsing top-down
 * 4. TOKENIZACIÓN: Reconocer elementos básicos (números, strings, etc.)
 * 5. GESTIÓN DE MEMORIA: Structures dinámicas enlazadas
 * 
 * FORMATO JSON SOPORTADO:
 * - Números enteros: 42, -17
 * - Strings: "hello", "escape \" test"  
 * - Maps/Objects: {"key": value, "key2": value2}
 * - Escape sequences: \\ y \" solamente
 */

 #include <stdio.h>
 #include <stdbool.h>
 #include <ctype.h>
 #include <string.h>
 #include <stdlib.h>
 
 // Definición de estructuras para el AST
 typedef struct json {
	 enum {
		 MAP,
		 INTEGER,
		 STRING
	 } type;
	 union {
		 struct {
			 struct pair *data;
			 size_t size;
		 } map;
		 int integer;
		 char *string;
	 };
 } json;
 
 typedef struct pair {
	 char *key;
	 json value;
 } pair;
 
 // Declaraciones de funciones
 int argo(json *dst, FILE *stream);
 int parser(json *dst, FILE *stream);
 int parse_int(json *dst, FILE *stream);
 int parse_string(json *dst, FILE *stream);
 int parse_map(json *dst, FILE *stream);
 void free_json(json j);
 
 /*
  * FUNCIONES AUXILIARES PARA PARSING:
  */
  
  // Función para mirar el siguiente carácter sin consumirlo
 int peek(FILE *stream)
 {
	 int c = getc(stream);
	 ungetc(c, stream);
	 return c;
 }
 
 // Función para reportar errores de parsing
 void unexpected(FILE *stream)
 {
	 if (peek(stream) != EOF)
		 printf("unexpected token '%c'\n", peek(stream));
	 else
		 printf("unexpected end of input\n");
 }
 
 // Función para aceptar un carácter específico
 int accept(FILE *stream, char c)
 {
	 if (peek(stream) == c)
	 {
		 (void)getc(stream);
		 return 1;
	 }
	 return 0;
 }
 
 // Función para requerir un carácter específico
 int expect(FILE *stream, char c)
 {
	 if (accept(stream, c))
		 return 1;
	 unexpected(stream);
	 return 0;
 }
 
char	*ft_strdup(const char *s)
{
	size_t	len;
	size_t	index;
	char	*s_dup;

	len = 0;
	index = 0;
	while (s[len] != '\0')
	{
		len++;
	}
	s_dup = (char *)malloc(len + 1);
	if (s_dup == NULL)
		return (NULL);
	while (index < len)
	{
		s_dup[index] = s[index];
		index++;
	}
	s_dup[index] = '\0';
	return (s_dup);
}

 int parse_map(json *dst, FILE *stream)
 {
	 pair *items = NULL;
	 size_t size = 0;
	 json key;
	 
	 if (!expect(stream, '{'))
		 return -1;
	 if (accept(stream, '}'))
	 {
		 dst->type = MAP;
		 dst->map.size = 0;
		 dst->map.data = NULL;
		 return 1;
	 }
	 while (1)
	 {
		 items = realloc(items, sizeof(pair) * (size + 1));
		 if (!items)
			 return -1;
		 // Parsear key (debe ser string)
		 if (parse_string(&key, stream) == -1)
		 {
			 free(items);
			 return -1;
		 }
		 // Esperar ':'
		 if (!expect(stream, ':'))
		 {
			 free(key.string);
			 free(items);
			 return -1;
		 }
		 // Parsear value (cualquier tipo JSON)
		 if (parser(&items[size].value, stream) == -1)
		 {
			 free(key.string);
			 free(items);
			 return -1;
		 }
		 // Guardar key
		 items[size].key = key.string;
		 size++;
		 // Verificar si hay más elementos
		 if (accept(stream, ','))
		 {
			 continue;
		 }
		 else if (peek(stream) == '}')
		 {
			 break;
		 }
		 else
		 {
			 unexpected(stream);
			 for (size_t j = 0; j < size; j++)
			 {
				 free(items[j].key);
				 free_json(items[j].value);
			 }
			 free(items);
			 return -1;
		 }
	 }
	 if (!expect(stream, '}'))
	 {
		 // Liberar memoria en caso de error
		 for (size_t j = 0; j < size; j++)
		 {
			 free(items[j].key);
			 free_json(items[j].value);
		 }
		 free(items);
		 return -1;
	 }
	 
	 // Configurar resultado
	 dst->type = MAP;
	 dst->map.size = size;
	 dst->map.data = items;
	 
	 return 1;
 }

 int parse_string(json *dst, FILE *stream)
 {
	 char buffer[4096];
	 char c;
	 int i = 0;
	 
	 // Consumir comilla de apertura
	 if (!expect(stream, '"'))
		 return -1;
	 while (1)
	 {
		 c = getc(stream);
		 if (c == EOF)
		 {
			 unexpected(stream);
			 return -1;
		 }
		 if (c == '"')  // Comilla de cierre
			 break;
		 if (c == '\\')  // Escape sequence
		 {
			 c = getc(stream);
			 if (c == EOF)
			 {
				 unexpected(stream);
				 return -1;
			 }
		 }
		 buffer[i++] = c;
		 if ((size_t)i >= sizeof(buffer) - 1)
		 {
			 unexpected(stream);
			 return -1;
		 }
	 }// end of while
	 buffer[i] = '\0';
	 dst->type = STRING;
	 dst->string = ft_strdup(buffer);
	 if (!dst->string)
		 return -1;
	 
	 return 1;
 }

 int parse_int(json *dst, FILE *stream)
 {
	 int n;
	 
	 if (fscanf(stream, "%d", &n) == 1)
	 {
		 dst->type = INTEGER;
		 dst->integer = n;
		 return 1;
	 }
	 unexpected(stream);
	 return -1;
 }

 int parser(json *dst, FILE *stream)
 {
	 int c = peek(stream);
	 
	 if (c == '"')
		 return parse_string(dst, stream);
	 else if (isdigit(c) || c == '-')
		 return parse_int(dst, stream);
	 else if (c == '{')
		 return parse_map(dst, stream);
	 else
	 {
		 unexpected(stream);
		 return -1;
	 }
 }

 int argo(json *dst, FILE *stream)
 {
	 return parser(dst, stream);
 }
 
 void free_json(json j)
 {
	 switch (j.type)
	 {
		 case MAP:
			 for (size_t i = 0; i < j.map.size; i++)
			 {
				 free(j.map.data[i].key);
				 free_json(j.map.data[i].value);
			 }
			 free(j.map.data);
			 break;
		 
		 case STRING:
			 free(j.string);
			 break;
		 
		 case INTEGER:
			 // No hay memoria que liberar
			 break;
	 }
 }
 
 void serialize(json j)
 {
	 switch (j.type)
	 {
		 case INTEGER:
			 printf("%d", j.integer);
			 break;
			 
		 case STRING:
			 putchar('"');
			 for (int i = 0; j.string[i]; i++)
			 {
				 if (j.string[i] == '\\' || j.string[i] == '"')
					 putchar('\\');
				 putchar(j.string[i]);
			 }
			 putchar('"');
			 break;
			 
		 case MAP:
			 putchar('{');
			 for (size_t i = 0; i < j.map.size; i++)
			 {
				 if (i != 0)
					 putchar(',');
				 json key_json = {.type = STRING, .string = j.map.data[i].key};
				 serialize(key_json);
				 putchar(':');
				 serialize(j.map.data[i].value);
			 }
			 putchar('}');
			 break;
	 }
 }
 
 int main(int argc, char **argv)
{
    if (argc != 2)
        return 1;
    
    char *filename = argv[1];
    FILE *stream = fopen(filename, "r");
    if (!stream)
        return 1;
    
    json file;
    
    if (argo(&file, stream) != 1)
    {
        free_json(file);
        fclose(stream);
        return 1;
    }
    
    serialize(file);
    printf("\n");
    
    free_json(file);
    fclose(stream);
    return 0;
}