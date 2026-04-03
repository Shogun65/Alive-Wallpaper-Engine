template<typename Pushframe, typename GetFrame, typename ReturnFrame>
void FFmpeg::RunDecoderLoop(Pushframe pushframe, GetFrame getframe, ReturnFrame returnframe)
{
	printf("Decoder thread Runing!\n");
	AVPacket* Packet = av_packet_alloc();

	while (_DecodedThreadruning)
	{
		printf("runing1\n");
		if (av_read_frame(_FormatContext, Packet) < 0)
		{
			// End Of File
			printf("Decoder thread stop!\n");
			break;
		}
		printf("runing2\n");
		if (Packet->stream_index == _VideoStreamIndex)
		{
			printf("runing3\n");
			avcodec_send_packet(_CodecContext, Packet);
			printf("runing4\n");
			while (true)
			{
				printf("runing5\n");
				AVFrame* frame = getframe();
				printf("runing6\n");
				int ret = avcodec_receive_frame(_CodecContext, frame);

				if (ret == AVERROR(EAGAIN) || ret == AVERROR_EOF)
				{
					printf("EAGAIN\n");
					returnframe(frame);
					break;
				}
				else if (ret < 0)
				{
					printf("Decoder error!\n");
				}
				else if (ret == 0)
				{
					printf("runing\n");
					pushframe(frame);
				}
			}

		}
		av_packet_unref(Packet);
	}
	av_packet_free(&Packet);
	printf("stop decoder\n");
}
