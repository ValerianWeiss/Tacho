package com.example.valerian.iot_tacho_v01;

import android.content.Context;
import android.os.AsyncTask;
import android.support.v7.app.AppCompatActivity;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.BaseAdapter;
import android.widget.ImageView;
import android.widget.ListView;
import android.widget.TextView;

import java.util.List;
import java.util.Vector;


/**
 * Created by Valerian on 05.11.2017.
 */

public class SelectWiFiActivityListThread extends AsyncTask<Void, Void, Void>
{
    private Context activity;
    private View listView;
    private int wifiImage = R.drawable.wifi;
    private List<String> wifiNetworkNames = new Vector<>();

    public SelectWiFiActivityListThread(Context context, View view)
    {
        this.activity = context;
        this.listView = view;
    }

    @Override
    protected Void doInBackground(Void... voids)
    {
        ListView wifiListView = (ListView) listView.findViewById(R.id.wifiList);
        ListViewAdapter listViewAdapter = new ListViewAdapter();
        wifiListView.setAdapter(listViewAdapter);
        return null;
    }

    class ListViewAdapter extends BaseAdapter
    {

        @Override
        public int getCount()
        {
            return wifiNetworkNames.size();
        }

        @Override
        public Object getItem(int i) {
            return null;
        }

        @Override
        public long getItemId(int i) {
            return 0;
        }

        @Override
        public View getView(int i, View view, ViewGroup viewGroup)
        {
            LayoutInflater inflater = (LayoutInflater) activity.getSystemService(activity.LAYOUT_INFLATER_SERVICE);
            view = inflater.inflate(R.layout.select_wifi_list_item,null);
            ImageView imageView = (ImageView) view.findViewById(R.id.wifiIcon);
            TextView textView = (TextView) view.findViewById(R.id.wifiNetworkName);

            imageView.setImageResource(wifiImage);
            String [] stringArray = wifiNetworkNames.toArray(new String[wifiNetworkNames.size()]);
            textView.setText(stringArray[i]);
            return view;
        }
    }
}
