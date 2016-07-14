package me.hxkandwal.video_analytics.demo.colorspace;

import java.awt.BorderLayout;
import java.awt.Dimension;
import java.awt.EventQueue;
import java.awt.Graphics;
import java.awt.GraphicsConfiguration;
import java.awt.GraphicsEnvironment;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;
import java.net.MalformedURLException;

import javax.imageio.ImageIO;
import javax.swing.JFrame;
import javax.swing.JPanel;

public class RGBToHSVConversion extends JPanel {

	private static final long serialVersionUID = 1L;

	private BufferedImage sourceImage;
	private int increaseValue;

	public BufferedImage getSourceImage() {
		return sourceImage;
	}

	public RGBToHSVConversion(String imagePath, int increaseValue) throws IOException {
		super();
		this.increaseValue = increaseValue;
		sourceImage = ImageIO.read(new File(imagePath));
		setPreferredSize(new Dimension(sourceImage.getWidth(), sourceImage.getHeight()));
	}

	public GraphicsConfiguration getGraphicsConfiguration() {
		return GraphicsEnvironment.getLocalGraphicsEnvironment().getDefaultScreenDevice().getDefaultConfiguration();
	}

	@Override
	public void paintComponent(Graphics g) {
		try {
			super.paintComponents(g);

			int width = getSourceImage().getRaster().getWidth();
			int height = getSourceImage().getRaster().getHeight();

			// create a shadow copy of the original image.
			final BufferedImage outputBufferedImage = getGraphicsConfiguration().createCompatibleImage(width, height,
					getSourceImage().getTransparency());

			int[] rgbPixel = new int[3];
			double[] hsvPixel = new double[3];

			for (int rowindex = 0; rowindex < height; rowindex++) {
				for (int columnindex = 0; columnindex < width; columnindex++) {
					// get the actual value to the pixel.
					getSourceImage().getRaster().getPixel(columnindex, rowindex, rgbPixel);

					// checking that adding offset should not cross 255, then
					// overflow will occur and value might get reset to 0
					rgbPixel[0] = ((rgbPixel[0] + increaseValue) > 255 ? 255 : (rgbPixel[0] + increaseValue));
					rgbPixel[1] = ((rgbPixel[1] + increaseValue) > 255 ? 255 : (rgbPixel[1] + increaseValue));
					rgbPixel[2] = ((rgbPixel[2] + increaseValue) > 255 ? 255 : (rgbPixel[2] + increaseValue));

					convertRGBtoHSV(rgbPixel, hsvPixel);

					// set the value to the shadow copy of the image.
					outputBufferedImage.getRaster().setPixel(columnindex, rowindex, hsvPixel);
				}
			}
			
			ImageIO.write(outputBufferedImage, "jpeg",
					new File(System.getProperty("user.dir") + "/image-100-rgb-hsv-brighness.jpeg"));

			g.drawImage(outputBufferedImage, 0, 0, width, 800, null);
			g.dispose();
		} catch (IOException e) {
			e.printStackTrace();
		}
	}

	public void convertRGBtoHSV(int[] rgbPixel, double[] hsvPixel) {
		int r = rgbPixel[0];
		int g = rgbPixel[1];
		int b = rgbPixel[2];

		double hue, saturation, value;

		int cmax = (r > g) ? r : g;
		if (b > cmax)
			cmax = b;
		int cmin = (r < g) ? r : g;
		if (b < cmin)
			cmin = b;

		value = ((double) cmax) / 255.0f;
		if (cmax != 0)
			saturation = ((double) (cmax - cmin)) / ((double) cmax);
		else
			saturation = 0;
		if (saturation == 0)
			hue = 0;
		else {
			double redc = ((double) (cmax - r)) / ((double) (cmax - cmin));
			double greenc = ((double) (cmax - g)) / ((double) (cmax - cmin));
			double bluec = ((double) (cmax - b)) / ((double) (cmax - cmin));
			if (r == cmax)
				hue = (greenc - bluec) / (cmax - cmin);
			else if (g == cmax)
				hue = 2.0f + (bluec - redc) / (cmax - cmin);
			else
				hue = 4.0f + (redc - greenc) / (cmax - cmin);

			hue /= 6.0f;

			if (hue < 0)
				hue = hue + 1.0f;
		}

		hsvPixel[0] = (hue * 255.d > 255 ? 255 : hue * 255.d);
		hsvPixel[1] = (saturation * 255.d > 255 ? 255 : saturation * 255.d);
		hsvPixel[2] = (value * 255.d > 255 ? 255 : value * 255.d);
	}

	public static void main(final String[] args) {

		if (args.length != 2) {
			System.out.println("\n Incorrect arguments passed ! To run this program, please provide two arguments : ");
			System.out.println(
					" a) Complete absolute path of the image file. example : C:/username/ ...... /fruit-plate-1.png ");
			System.out.println(" b) The increase value for the Brightness like : 10, 50, 100 \n\n");
			System.exit(1);
		} else {
			EventQueue.invokeLater(new Runnable() {
				public void run() {
					try {
						JFrame frame = new JFrame();
						frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

						RGBToHSVConversion adjustBrightness = new RGBToHSVConversion(args[0], Integer.valueOf(args[1]));

						frame.add(adjustBrightness, BorderLayout.CENTER);
						frame.pack();
						frame.setVisible(true);
					} catch (MalformedURLException e) {
						e.printStackTrace();
					} catch (IOException e) {
						e.printStackTrace();
					}
				}
			});
		}
	}

}