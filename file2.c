#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    // Ouvrir un fichier en écriture
    int file_descriptor = open("mon_fichier.txt", O_CREAT | O_WRONLY | O_TRUNC, S_IRUSR | S_IWUSR);
    
    if (file_descriptor == -1) {
        perror("Erreur lors de l'ouverture du fichier");
        exit(EXIT_FAILURE);
    }

    // Écrire dans le fichier
    const char* texte_a_ecrire = "Hello, world!\n";
    ssize_t bytes_ecrits = write(file_descriptor, texte_a_ecrire, strlen(texte_a_ecrire));

    if (bytes_ecrits == -1) {
        perror("Erreur lors de l'écriture dans le fichier");
        close(file_descriptor);
        exit(EXIT_FAILURE);
    }

    // Fermer le fichier après l'écriture
    close(file_descriptor);

    // Ouvrir le fichier en lecture
    file_descriptor = open("mon_fichier.txt", O_RDONLY);

    if (file_descriptor == -1) {
        perror("Erreur lors de l'ouverture du fichier en lecture");
        exit(EXIT_FAILURE);
    }

    // Lire depuis le fichier
    char buffer[100];
    ssize_t bytes_lus = read(file_descriptor, buffer, sizeof(buffer));

    if (bytes_lus == -1) {
        perror("Erreur lors de la lecture depuis le fichier");
        close(file_descriptor);
        exit(EXIT_FAILURE);
    }

    // Afficher le contenu lu
    printf("Contenu du fichier :\n%s", buffer);

    // Fermer le fichier après la lecture
    close(file_descriptor);

    return 0;
}
