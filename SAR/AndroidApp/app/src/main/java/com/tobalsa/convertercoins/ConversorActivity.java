package com.tobalsa.convertercoins;

import android.os.Bundle;
import android.support.design.widget.FloatingActionButton;
import android.support.design.widget.Snackbar;
import android.support.v7.app.AppCompatActivity;
import android.support.v7.widget.Toolbar;
import android.view.View;
import android.widget.Button;
import android.widget.SeekBar;
import android.widget.TextView;

public class ConversorActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_conversor);
        Toolbar toolbar = (Toolbar) findViewById(R.id.toolbar);
        setSupportActionBar(toolbar);

        getSupportActionBar().setDisplayHomeAsUpEnabled(true);

        SeekBar sbValor = (SeekBar) findViewById(R.id.sbCantidad);
        Button btnConvertir = (Button) findViewById(R.id.btnConvertir);
        final TextView tvValor = (TextView) findViewById(R.id.tvValor);

        tvValor.setText("0");

        sbValor.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {
            @Override
            public void onProgressChanged(SeekBar seekBar, int progress, boolean b) {
                tvValor.setText(""+progress);
            }
            @Override
            public void onStartTrackingTouch(SeekBar seekBar) {}
            @Override
            public void onStopTrackingTouch(SeekBar seekBar) {}
        });

        btnConvertir.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                int cantidad = Integer.parseInt(tvValor.getText().toString());
                double cantResultado = cantidad * 0.94;

                final TextView tvResultado = (TextView) findViewById(R.id.tvResultado);

                tvResultado.setText("Tus "+cantidad+" dolares son "+String.format("%2f", cantResultado)+" euros.");

            }
        });

    }

}
