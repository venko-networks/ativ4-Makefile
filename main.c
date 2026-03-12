#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <openssl/md5.h> 

void* tarefa_thread(void* arg) {
    printf("[Thread %s] Iniciada.\n", (char*)arg);
    sleep(1);
    return NULL;
}

int main() {
    // 1. Dependência (Running time e compilação)?
    printf("Verificando se o utilitário 'curl' existe no sistema...\n");
    if (system("which curl > /dev/null 2>&1") != 0) {
        fprintf(stderr, "Erro: Dependência de execução (curl) não encontrada!\n");
        return 1;
    }

    // 2. Uso da OpenSSL (Dependência de Compilação ou execução)
    unsigned char digest[MD5_DIGEST_LENGTH];
    const char* string = "Elsys_Challenge";
    MD5((unsigned char*)string, 15, digest);

    printf("Hash MD5 de teste: ");
    for(int i = 0; i < MD5_DIGEST_LENGTH; i++) printf("%02x", digest[i]);
    printf("\n");

    pthread_t t1;
    pthread_create(&t1, NULL, tarefa_thread, "Worker");
    pthread_join(t1, NULL);

    return 0;
}
