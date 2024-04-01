//package client;
//
//import protocol.MsgScoreEntry;
//
//import java.io.IOException;
//import java.io.ObjectOutputStream;
//import java.util.ArrayList;
//import java.util.TimerTask;
//
//class MySendDataTask extends TimerTask {
//    public ArrayList<MsgScoreEntry> score_entries;
//    public int start_pos = 0;
//    final int BATCH_SIZE = 20;
//    public ObjectOutputStream output_stream;
//
//    public MySendDataTask(ArrayList<MsgScoreEntry> score_entries, ObjectOutputStream output_stream) {
//        this.score_entries = score_entries;
//        this.output_stream = output_stream;
//    }
//
//    @Override
//    public void run() {
//        MsgScoreEntry[] score_entries_batch = new MsgScoreEntry[20];
//        for (int i = 0; i < BATCH_SIZE && start_pos + i < score_entries.size(); i++) {
//            score_entries_batch[i] = score_entries.get(start_pos + i);
//        }
//        try{
//            output_stream.writeObject(score_entries_batch);
//        } catch (IOException ex) {
//            ex.printStackTrace();
//        }
//        start_pos += BATCH_SIZE;
//    }
//}
