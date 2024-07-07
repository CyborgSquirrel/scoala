[[mecanism de sincronizare]]

Tip abstract de date care constă din:
- variabile reprezentând resursa critică
- proceduri ce reprezintă operații asupra resursei critice
- corp de inițializare

Proprietăți:
- codul de inițializare este executat înaintea oricărui conflict asupra datelor
- numai una dintre procedurile monitorului poate fi executată la un moment dat