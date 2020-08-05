# Atividade 04

A partir do código disponibilizado pelo professor ([link](https://github.com/jmhal/parallel/tree/master/jacobi)), tentei algumas modificações usando as _'pragmas'_ do openmp descritas a seguir:
* **colapse:** não achei que caberia o uso deste, pois tinham laços for não aninhados dentro de alguns aninhados.
* **nested:** tentei usar esta diretiva, entretanto como resultado obtive algumas inconsistenciase por isso optei por não mantê-la.
* **static ou dynamic:** usando estas diretivas, acredito que por se tratar de um programa com uma entrada grande e tantas interações eu não percebi tantas diferenças.

Os melhores resultados que obtive foram usando apenas as diretivas _'parallel for'_, com os seguintes resultados:

```
Número de cores     Tempo de Execução       Diferença
2                   0m17.859s               1.73947
4                   0m9.587s                1.81802
8                   0m7.263s                1.40474
12                  0m5.428s                1.08398
```