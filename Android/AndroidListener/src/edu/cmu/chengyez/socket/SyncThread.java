package edu.cmu.chengyez.socket;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;

import android.util.Log;

public class SyncThread extends Thread {
	private InputStream input;
	private OutputStream output;
	private static final String TAG = SyncThread.class.getName();
	private boolean stopped = false;
	private boolean stopSignal = false;

	public static final int MAXBUFSIZE = 1024;

	public void sendStopSignal() {
		synchronized (this) {
			stopSignal = true;
		}
	}

	public boolean isStopped() {
		return stopped;
	}

	public SyncThread(OutputStream outputStream, InputStream inputStream) {
		input = inputStream;
		output = outputStream;
	}

	@Override
	public void run() {
		stopped = false;

		byte[] buf = new byte[MAXBUFSIZE];
		int readBytes = 0;
		try {
			while (true) {
				if (stopSignal) {
					break;
				}
				if (input.available() > 0) {
					readBytes = input.read(buf, 0, MAXBUFSIZE);
					Log.d(TAG, this.getName() + ": Read " + readBytes
							+ " bytes from input");
					output.write(buf, 0, readBytes);
					output.flush();
				}
			}
		} catch (IOException e) {
			Log.d(TAG, this.getName() + ": Error");
		}

		stopped = true;
		Log.d(TAG, this.getName() + ": Stopped");
	}

}
