package common;

import protocol.MsgScoreEntry;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;

public class Common {
    public static ArrayList<MsgScoreEntry> extractScoreEntries(BufferedReader reader, int country) {
        ArrayList<MsgScoreEntry> scoreEntries = new ArrayList<>();
        try {
            String line;
            while ((line = reader.readLine()) != null) {
                String[] parts = line.split(",");
                int id = Integer.parseInt(parts[0].trim());
                int score = Integer.parseInt(parts[1].trim());

                MsgScoreEntry score_entry = new MsgScoreEntry(id, score, country);

                scoreEntries.add(score_entry);
            }
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
        return scoreEntries;
    }
}
