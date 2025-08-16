# Plan de proiect: Translatare EventPlanner din CLI în GUI cu Qt

## 1. Pregătire și setup

- Confirmă funcționalitatea EventManager și Event (unit-test, eventual).
- Asigură-te că Qt6 este instalat și integrat în CLion.
- Modifică `CMakeLists.txt` pentru a include Qt6 Widgets:
  ```cmake
  find_package(Qt6 REQUIRED COMPONENTS Widgets)
  target_link_libraries(EventPlanner PRIVATE Qt6::Widgets)
  ```

## 2. Refactorizare minimă a codului existent

- **Separă logica de interfață:**  
  EventManager, Event rămân nemodificați (poate doar să adaugi metode care returnează mesaje, nu doar să afișeze direct
  în consolă).
- Înlocuiește (sau suprascrie) metodele care folosesc `std::cout` cu metode care returnează `std::string` pentru
  feedback.

## 3. Creare fereastră principală (MainWindow)

- Creează o clasă derivată din `QMainWindow` sau `QWidget`.
- Adaugă un layout vertical cu:
    - QTableView/QListWidget pentru afișarea evenimentelor
    - Butoane pentru Adăugare, Editare, Ștergere, Căutare
    - Butoane pentru Salvează/Încarcă evenimente (opțional)
    - Un label sau status bar pentru feedback

## 4. Implementare adăugare/editare/ștergere eveniment

- Creează **dialoguri dedicate** (QDialog/QInputDialog) pentru introducerea/actualizarea datelor unui eveniment.
- La acțiunea unui buton (ex: "Adaugă"), deschide dialogul, preia datele și apelează EventManager.

## 5. Conectare semnale și sloturi

- Folosește semnale și sloturi pentru a lega acțiunile din GUI cu metodele EventManager:
    - Ex: `connect(addButton, &QPushButton::clicked, ...)`
- Actualizează lista de evenimente din GUI la fiecare modificare.

## 6. Afișare și actualizare dinamică listă evenimente

- Folosește un model Qt (QStandardItemModel sau custom QAbstractTableModel) pentru a popula tabelul/lista cu evenimente.
- La adăugare/editare/ștergere, actualizează modelul.

## 7. Implementare funcții de căutare și notificare

- Adaugă câmp de căutare și buton (sau filtru dinamic).
- Pentru notificări de evenimente viitoare, afișează un mesaj/label în GUI.

## 8. Salvare și încărcare din fișier

- Integrează funcțiile existente EventManager cu GUI (folosind QInputDialog pentru nume fișier sau direct).

## 9. Testare și optimizări

- Testează toate acțiunile în GUI.
- Opțional: adaugă validări suplimentare, styling, shortcut-uri, etc.

## 10. Extra (opțional, după MVP)

- Undo/Redo
- Export în format JSON/XML
- Sincronizare cu rețea/server
- Notificări sistem

---

### Structura sugerată de fișiere

- `main.cpp` – pornește aplicația Qt
- `mainwindow.h/cpp` – logica ferestrei principale
- `eventdialog.h/cpp` – dialog pentru adăugare/editare eveniment
- `eventmanager.h/cpp` – logică business
- `event.h/cpp` – clasa Event
- `eventmodel.h/cpp` – model custom pentru tabel (dacă vrei să folosești QTableView)

---

## Ordinea de lucru recomandată

1. Setup Qt și modifică CMakeLists.txt.
2. Creează MainWindow cu listă și butoane.
3. Adaugă dialoguri pentru CRUD.
4. Conectează EventManager cu GUI.
5. Populează și actualizează lista de evenimente.
6. Integrează funcții de căutare/salvare/încărcare.
7. Testează și optimizează.