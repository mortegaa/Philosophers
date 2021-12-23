# Philosophers
Los filósofos es un famoso problema de la programación que trata la sincronización de procesos y las técnicas que utilizar para resoverlo.
Los filósofos se sientan en una mesa redonda y hay un bol de spaguetties en el centro de la misma. Para poder comer un filósofo necesita 2 tenedores ya que con sólo uno es un poco complicado.
EL número de tenedores que hay en la mesa es el mismo que el de comensales. Un tenedor sólo puede ser utilzado por sólo filósofo.

Yo lo he hecho de 2 maneras diferentes:
* ## Hilos Y Mutex
Los filósofos se sientan como he dicho anteriormente y hay un tenedor a la izquierda y otro a la derecha de cada filósofo.
Aquí cada filósofo es un hilo (thread) y comparten los recursos que son los tenedores. Los tenedores son protegidos por mutex.

* ## Procesos y semáfaros

En este caso todos los tenedores están en el centro de la mesa y cada uno puede coger el que prefiera. Aquí cada filósofo es un proceso hijo del programa principal y los tenedores son protegidos con un semáfaro.
