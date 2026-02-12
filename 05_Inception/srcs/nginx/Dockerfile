# Dockerfile
FROM alpine:3.18

# Actualizamos los paquetes e instalamos Nginx y OpenSSL.
# OpenSSL es necesario para la configuración de TLS [1].
RUN apk add --no-cache nginx openssl

# Creamos el directorio para los certificados SSL dentro del contenedor.
RUN mkdir -p /etc/nginx/ssl

# Copiamos nuestra configuración personalizada de Nginx al contenedor.
# Este archivo definirá el uso de TLSv1.2 o TLSv1.3 [1].
COPY conf/nginx.conf /etc/nginx/nginx.conf

# Exponemos el puerto 443, ya que Nginx debe ser el único punto de entrada HTTPS [1].
EXPOSE 443

# Comando para iniciar Nginx. El "daemon off;" es esencial para que Nginx se ejecute en primer plano
# y el contenedor no se cierre inmediatamente.
CMD ["nginx", "-g", "daemon off;"]
